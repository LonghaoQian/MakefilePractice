/*************************************************************

MIT License

Copyright (c) 2024 Dr. Longhao Qian

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*************************************************************/

#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include <stack>
#include <map>
#include <functional>
#include <algorithm>

class DataStruct {
    public:
    DataStruct(double val) {
        val_ = val;
    };
    double val_{0.0};
    ~DataStruct() = default;

    
    // // evaluate at copy assignment 
    // DataStruct& operator=(const ExpressionBase& expr) {
    //     std::cout<<"ready to parse the expression\n";
    // }
};


// base of an expression class
// provide interface to operations
// a storage records all the operations

// model the expression as a binary tree
enum ExprPlace {
    LHS,
    RHS,
    NONE
};

enum OperationType {
    Data,
    Add,
    Sub,
    Matrix_Product,
    Scalar_Product,
    Const_Product,
    Scalar_Division,
    Const_Division
};

enum OperationLevel {
    LEVEL_0, // level 0 contains data
    LEVEL_1, // level 1 contains sum and subtraction
    LEVEL_2, // level 2 contains scalar division and multiplication
    LEVEL_3, // level 3 contains matrix multiplication
};

class ExpressionNode {
    public:
    ExpressionNode() {};
    ExpressionNode(double val) : val_{val} {
    };
    ExpressionNode(OperationType type,
                   OperationLevel level,
                   std::shared_ptr<ExpressionNode> lhs,
                   std::shared_ptr<ExpressionNode> rhs) {
        type_ = type;
        level_ = level;
        lhs_ = lhs;
        rhs_ = rhs;
    }
    ~ExpressionNode() = default;
    OperationType type_{Data};
    OperationLevel level_{LEVEL_0};
    double val_{0.0};
    // used for storing the processed computation graph in a multi-branch tree
    using SubNodeList = std::vector<std::pair<OperationType, std::shared_ptr<ExpressionNode>> >;
    SubNodeList subNodeList;
    // used for generate initial computation graph using a binary tree;
    std::shared_ptr<ExpressionNode> lhs_;
    std::shared_ptr<ExpressionNode> rhs_;
    void Display(void)
    {
        switch (type_) {
            case OperationType::Data: {
                std::cout<<"expr: Data \n";
                break;
            }
            case OperationType::Add: {
                 std::cout<<"expr: Add \n";
                 break;
            }
            case OperationType::Matrix_Product: {
                 std::cout<<"expr: Matrix Product \n";
                 break;
            }
            default: {
                std::cout<<"undefined \n";
                break;
            }
        }
    };
};

static std::map<OperationType, std::function<OperationType(OperationType)>> operationSwapTable {
    {OperationType::Add, [](OperationType t) {
        return t;
    }},

    {OperationType::Sub, [](OperationType t) {
        if (t == OperationType::Add) {
            return OperationType::Sub;
        } else if (t == OperationType::Sub) {
            return OperationType::Add;
        } else {
            return t;
        }
    }},

    {OperationType::Scalar_Product, [](OperationType t) {
        return t;
    }},

    {OperationType::Scalar_Division, [](OperationType t) {
        if (t == OperationType::Scalar_Product) {
            return OperationType::Scalar_Division;
        } else if (t == OperationType::Scalar_Product) {
            return OperationType::Scalar_Product;
        } else {
            return t;
        }
    }},

};

using OperationStack = std::stack<std::pair<ExprPlace, std::shared_ptr<ExpressionNode>>>;

static std::map<OperationLevel, std::function<OperationType(ExprPlace, OperationType)>> lhsTypeMapTable{
    {OperationLevel::LEVEL_1,
    [](ExprPlace place, OperationType parentType) {
        if (place == ExprPlace::NONE || place == ExprPlace::LHS) {
            return OperationType::Add;
        } else {
            return parentType;
        }
    }},
    {OperationLevel::LEVEL_2,
    [](ExprPlace place, OperationType parentType) {
        if (place == ExprPlace::NONE || place == ExprPlace::LHS) {
            return OperationType::Scalar_Product;
        } else {
            return parentType;
        }
    }},
};

//  add the child sublist to the parent sublist and release the child node
void AddSubNodeListToParent(OperationStack& buffer,
                            std::shared_ptr<ExpressionNode> child,
                            ExprPlace childPlace)
{
    // top of the buffer should be the parent
    auto parent = buffer.top().second.get();
    
    if (parent == nullptr || child == nullptr) {
        return;
    }
    if (parent->type_ == OperationType::Data) {
        // parent operator type must not be data
        return;
    }
    if (childPlace == ExprPlace::NONE) {
        // if none, then this node is the root node, do nothing
        return;
    }
    if (child->level_ != parent->level_) {
        // if child level is not the same as the parent level
        // push the child node ptr to the subnodeList of the parent node
        buffer.top().second->subNodeList.emplace_back(lhsTypeMapTable[parent->level_](childPlace, parent->type_),
                                                      child);
    } else {
        // if child level is the same as the parent node
        // move the child sublist to the parent sublist, and relase child node
        if (childPlace == ExprPlace::LHS) {
            for (auto& t : child->subNodeList) {
                parent->subNodeList.emplace_back(t.first, t.second);
            }
        } else {
            for (auto& t : child->subNodeList) {
                // if RHS, need to swap signs according to the parent type
                parent->subNodeList.emplace_back(operationSwapTable[parent->type_](t.first), t.second);
            }
        }
    }
}

    // parse the computational graph
    void ParseGraph(std::shared_ptr<ExpressionNode> root) {
        // if the root node is data, do nothing
        if ((root == nullptr) || (root->type_ == OperationType::Data)) {
            return;
        }
        OperationStack buffer;
        buffer.push({ExprPlace::NONE, root});
        std::shared_ptr<ExpressionNode> topTemp; // to hold the top elements of the stack
        while (!buffer.empty()) {
            // if lhs and rhs are empty, pop the node
            topTemp.reset();
            if ((buffer.top().second->lhs_ == nullptr) && (buffer.top().second->rhs_ == nullptr)) {
                // safe the top of the buffer
                topTemp = buffer.top().second;
                auto expPlace = buffer.top().first;
                // pop first
                buffer.pop();
                // if the current node has a parent
                if (!buffer.empty()) {
                    // after poping, add the information of the child node
                    // to the parent subNodeList
                    // AddSubNodeListToParent(buffer, buffer.top().second.get(), topTemp.get(), expPlace);
                    AddSubNodeListToParent(buffer, topTemp, expPlace);
                }
            } else if (buffer.top().second->lhs_ != nullptr) {
                // traverse the lhs
                topTemp = buffer.top().second->lhs_;
                buffer.top().second->lhs_.reset();// remove the connection
                // add the node to the stack
                buffer.push({ExprPlace::LHS, topTemp});
            } else {
                // traverse the rhs
                topTemp = buffer.top().second->rhs_;
                buffer.top().second->rhs_.reset();// remove the connection
                // add the node to the stack
                buffer.push({ExprPlace::RHS, topTemp});
            }
        }

    };

    static std::map<OperationLevel, std::function<double(const ExpressionNode::SubNodeList&)>> evalTable {
        {OperationLevel::LEVEL_1, [](const ExpressionNode::SubNodeList& input){
            double res = 0.0;
            for (auto& t : input) {
                switch (t.first) {
                    case OperationType::Add: {
                        res += t.second->val_;
                        break;
                    }
                    case OperationType::Sub: {
                        res -= t.second->val_;
                        break;
                    }
                    default: {

                    }
                }
            }
            return res;
        }},
        {OperationLevel::LEVEL_2, [](const ExpressionNode::SubNodeList& input){
            double res = 1.0;
            for (auto& t : input) {
                switch (t.first) {
                    case OperationType::Scalar_Division: {
                        res /= t.second->val_;
                        break;
                    }
                    case OperationType::Scalar_Product: {
                        res *= t.second->val_;
                        break;
                    }
                    default: {

                    }
                }
            }
            return res;
        }},
    };

    void EvaluateNode(ExpressionNode* node) {
        if (node == nullptr) {
            return;
        }
        // evaluate using dispatch table
        node->val_ = evalTable[node->level_](node->subNodeList);
        // after evaluate, set the current node type to Data
        node->type_ = OperationType::Data;
        node->level_ = OperationLevel::LEVEL_0;
    }

    void EvalGraph(std::shared_ptr<ExpressionNode> root) {
        // if the root node is data, do nothing
        if ((root == nullptr) || (root->type_ == OperationType::Data)) {
            return;
        }
        // traverse using subOpList
        std::stack<std::shared_ptr<ExpressionNode>> buffer;
        buffer.push(root);
        while (!buffer.empty()) {
            // if the current node is data, do nothing and pop
            if (buffer.top()->type_ == OperationType::Data) {
                buffer.pop();
            } else {
                auto itr = std::find_if(buffer.top()->subNodeList.begin(), buffer.top()->subNodeList.end(),
                    [](const std::pair<OperationType, std::shared_ptr<ExpressionNode>>& input) {
                        return input.second->type_ != OperationType::Data;
                });
                if (itr == buffer.top()->subNodeList.end()) {
                    // if sublist contains only pointers to data
                    EvaluateNode(buffer.top().get());
                } else {
                    // if sublist contains pointers to other expression, push this
                    // node to the top of the stack
                    buffer.push(itr->second);
                }
            }
        }
    }

class ExpressionBase {
    public:
    ExpressionBase(double val)
    {
        node = std::make_shared<ExpressionNode>(val);
    };
    ExpressionBase(OperationType type,
                   OperationLevel level,
                   std::shared_ptr<ExpressionNode> lhs,
                   std::shared_ptr<ExpressionNode> rhs)
    {
        node = std::make_shared<ExpressionNode>(type, level, lhs, rhs);
    };
    ~ExpressionBase() = default;
    ExpressionBase(const ExpressionBase& obj)
    {
        std::cout<<"copy construction function has been called! \n";
        node = obj.node;
        if (obj.node->type_ != OperationType::Data) {
            // 1st traversal, parse the compuatitional topology
            ParseGraph(node);
            // 2nd traversal, evaluate the expression
            EvalGraph(node);
        }
    };
    ExpressionBase &operator=(const ExpressionBase& obj)
    {
        // assigning is special
        // by assigning, the lhs expression has a data type of data
        // valuate the expression
        std::cout<<"copy assignment function has been called! \n";
        if (this == &obj) {
            return *this;
        }
        node.reset(); // release the ownership of the previous content
        // if the obj is Data, then directly copy
        node = obj.node;
        if (obj.node->type_ != OperationType::Data) {
            // 1st traversal, parse the compuatitional topology
            ParseGraph(node);
            // 2nd traversal, evaluate the expression
            EvalGraph(node);
        }
        return *this;
    };
    ExpressionBase(ExpressionBase&& obj) noexcept
    {
        std::cout<<"move construction function has been called! \n";
        node = obj.node;
        obj.node.reset();
        if (obj.node->type_ != OperationType::Data) {
            // 1st traversal, parse the compuatitional topology
            ParseGraph(node);
            // 2nd traversal, evaluate the expression
            EvalGraph(node);
        }
    };
    ExpressionBase &operator=(ExpressionBase&& obj) noexcept
    {
        std::cout<<"copy move function has been called! \n";
        if (this == &obj) {
            return *this;
        }
        node.reset(); // release the ownership of the previous content
        node = obj.node;
        if (obj.node->type_ != OperationType::Data) {
            // 1st traversal, parse the compuatitional topology
            ParseGraph(node);
            // 2nd traversal, evaluate the expression
            EvalGraph(node);
        }
        return *this;
    };
    ExpressionBase Add(const ExpressionBase& other) {
        return ExpressionBase(OperationType::Add, OperationLevel::LEVEL_1, this->node, other.node);
    };

    ExpressionBase operator+(const ExpressionBase& other) {
        return Add(other);
    }
    ExpressionBase Product(const ExpressionBase& other) {
        return ExpressionBase(OperationType::Scalar_Product, OperationLevel::LEVEL_2, this->node, other.node);
    };
    ExpressionBase Product(double other) {
        return ExpressionBase(OperationType::Scalar_Product,
                              OperationLevel::LEVEL_2,
                              this->node,
                              ExpressionBase(other).node);
    }
    ExpressionBase operator*(const ExpressionBase& other) {
        return Product(other);
    };

    // evaluate the expression at custom type conversion function
    operator DataStruct() const {
        std::cout<<"type conversion is called! \n";
        if (node->type_ != OperationType::Data) {
            // 1st traversal, parse the compuatitional topology
            ParseGraph(node);
            // 2nd traversal, evaluate the expression
            EvalGraph(node);
        }
        return DataStruct(node->val_);
    };
    std::shared_ptr<ExpressionNode> node;
};

// addition and subtractiong
// level 1
ExpressionBase operator+(const DataStruct& lhs, const DataStruct& rhs) {
    return ExpressionBase(OperationType::Add,
                          OperationLevel::LEVEL_1,
                          ExpressionBase(lhs.val_).node,
                          ExpressionBase(rhs.val_).node);
}

ExpressionBase operator-(const DataStruct& lhs, const DataStruct& rhs) {
    return ExpressionBase(OperationType::Sub,
                          OperationLevel::LEVEL_1,
                          ExpressionBase(lhs.val_).node,
                          ExpressionBase(rhs.val_).node);
}

// scalar product
// level 2
ExpressionBase operator*(double val, const ExpressionBase& expr) {
    return ExpressionBase(OperationType::Scalar_Product,
                          OperationLevel::LEVEL_2,
                          ExpressionBase(val).node,
                          expr.node);
}

// ExpressionBase operator*(const ExpressionBase& expr, double val) {
//     return val * expr;
// }

ExpressionBase operator*(double val, const DataStruct& rhs) {
    return ExpressionBase(OperationType::Scalar_Product,
                          OperationLevel::LEVEL_2,
                          ExpressionBase(val).node,
                          ExpressionBase(rhs.val_).node);
}

// level 2
// scalar product
ExpressionBase operator*(const DataStruct& lhs, const DataStruct& rhs) {
    return ExpressionBase(OperationType::Scalar_Product,
                          OperationLevel::LEVEL_2,
                          ExpressionBase(lhs.val_).node,
                          ExpressionBase(rhs.val_).node);
}


ExpressionBase operator*(const DataStruct& lhs, const ExpressionBase& rhs) {
    return ExpressionBase(OperationType::Scalar_Product,
                          OperationLevel::LEVEL_2,
                          ExpressionBase(lhs.val_).node,
                          rhs.node);
}

ExpressionBase operator*(const ExpressionBase& lhs, const DataStruct& rhs) {
    return ExpressionBase(OperationType::Scalar_Product,
                          OperationLevel::LEVEL_2,
                          lhs.node,
                          ExpressionBase(rhs.val_).node);
}

// scalar division
ExpressionBase operator/(const DataStruct& lhs, const DataStruct& rhs) {
    return ExpressionBase(OperationType::Scalar_Division,
                          OperationLevel::LEVEL_2,
                          ExpressionBase(lhs.val_).node,
                          ExpressionBase(rhs.val_).node);
}

ExpressionBase operator/(const ExpressionBase& lhs, const DataStruct& rhs) {
    return ExpressionBase(OperationType::Scalar_Division,
                          OperationLevel::LEVEL_2,
                          lhs.node,
                          ExpressionBase(rhs.val_).node);
}

ExpressionBase operator/(const DataStruct& lhs, const ExpressionBase& rhs) {
    return ExpressionBase(OperationType::Scalar_Division,
                          OperationLevel::LEVEL_2,
                          ExpressionBase(lhs.val_).node,
                          rhs.node);
}

ExpressionBase operator/(const ExpressionBase& lhs, const ExpressionBase& rhs) {
    return ExpressionBase(OperationType::Scalar_Division,
                          OperationLevel::LEVEL_2,
                          lhs.node,
                          rhs.node);
}


ExpressionBase operator/(const DataStruct& lhs, double rhs) {
    return ExpressionBase(OperationType::Scalar_Division,
                          OperationLevel::LEVEL_2,
                          ExpressionBase(lhs.val_).node,
                          ExpressionBase(rhs).node);
}


ExpressionBase operator/(const ExpressionBase& lhs, double rhs) {
    return ExpressionBase(OperationType::Scalar_Division,
                          OperationLevel::LEVEL_2,
                          lhs.node,
                          ExpressionBase(rhs).node);
}

int main(void)
{
    DataStruct data1(-1.3);
    DataStruct data2(2.5);

    DataStruct exp1 = data1 - data2;
    std::cout<<exp1.val_<<'\n';
    DataStruct res = 2.0 * exp1 + data1 * (data1 + data2) * 3.0;

    std::cout<<"res: "<<res.val_<<'\n';
    std::cout<<"ref: " << 2.0 * (data1.val_ - data2.val_)
        + data1.val_ * ( data1.val_ +  data2.val_) * 3.0<<'\n';

    DataStruct data3(10.0);
    DataStruct data4(-3.2);
    DataStruct data5 = data3 * data4 * 2.0;

    std::cout<<"data5 :" <<data5.val_ <<'\n';
    std::cout<<"data5 ref: "<<data3.val_ * data4.val_ * 2.0 <<'\n';

    DataStruct data6(20.1);
    DataStruct data7 = (data3 + data4)/data6/4.2;

    std::cout<<"data7 :" <<data7.val_ <<'\n';
    std::cout<<"data7 ref: "<<(data3.val_ + data4.val_)/data6.val_/4.2 <<'\n';

    return 0;
}