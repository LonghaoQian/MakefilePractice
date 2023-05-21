/*************************************************************

MIT License

Copyright (c) 2023 Dr. Longhao Qian

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

#include "GraphCommon.h"

namespace GraphAnalysis
{
NodeBuffer::NodeBuffer(unsigned int maxSize_) : maxSize(maxSize_)
{
    Reset(maxSize_);
}

NodeBuffer::~NodeBuffer() {}
void NodeBuffer::Reset(unsigned int intmaxSize_)
{
    // clear data buffer
    buffer.clear();
    buffer.shrink_to_fit();
    maxSize = intmaxSize_;
    buffer.reserve(maxSize);
    // resize and initialize flag buffer
    inbuffer.clear();
    inbuffer.shrink_to_fit();
    inbuffer.reserve(maxSize);
    for (unsigned int i = 0; i < maxSize; i++) {
        inbuffer.emplace_back(std::make_pair(false, 0u));
    }
}
void NodeBuffer::Push(const Node &node)
{
    buffer.emplace_back(node);
    inbuffer[node.index].first = true;
    inbuffer[node.index].second = buffer.size() - 1u;
}
void NodeBuffer::Pop()
{
    inbuffer[buffer.back().index].first = false;
    inbuffer[buffer.back().index].second = 0u;
    buffer.pop_back();
}
Node &NodeBuffer::Top()
{
    return buffer.back();
}
bool NodeBuffer::IsEmpty()
{
    return buffer.empty();
}
bool NodeBuffer::ExceedSizeLimit()
{
    return buffer.size() > maxSize;
}
Node &NodeBuffer::GetBufferElement(unsigned int index)
{
    return buffer[index];
}
std::pair<bool, int> NodeBuffer::IsInBuffer(unsigned int index)
{
    return inbuffer[index];
}
unsigned int NodeBuffer::GetBufferSize()
{
    return buffer.size();
}
void NodeBuffer::DisplayElementbyIndex(unsigned int index_)
{
    auto it = std::find_if(
        buffer.begin(), buffer.end(),
        [index_](const Node &t) { return t.index == index_; });
    if (it == buffer.end()) {
        std::cout << "index = " << index_ << " is not in buffer!\n";
    } else {
        std::cout << "index = " << index_
                  << " is in buffer. Current stack top is: "
                  << it->edgeList.back().first << "\n";
    }
}
std::vector<Node> GetNodeFromAdjMatrix(const AdjacencyXi &input)
{
    std::vector<Node> res;
    auto numOfNodes = static_cast<unsigned int>(input.rows());
    res.reserve(numOfNodes);
    for (unsigned int i = 0u; i < numOfNodes; i++) {
        res.emplace_back(Node(i, 0.0));
        for (unsigned int j = 0u; j < numOfNodes; j++) {
            if (input(i, j) == 1) {
                res.back().AddAdjacent(j, 0.0);
            }
        }
    }
    return res;
}
}  // namespace GraphAnalysis