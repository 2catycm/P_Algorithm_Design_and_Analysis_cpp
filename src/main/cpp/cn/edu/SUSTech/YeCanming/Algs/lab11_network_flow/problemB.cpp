//
// Created by 叶璨铭 on 2022/5/22.
//
//And then you ask
//"Do you wanna dance, my barefoot cinderella?
// Don't need no slippers or party dress,
// the way you're lookin' right now is what I like the best."
#include "DinicFlowNetwork.h"
//#include "EdmondsKarpFlowNetwork.h"

#include <iostream>
/**
 * 1 ... 2n 表示学生。 2n+1...2n+n表示跳舞组。2n+n+1 和 2n+n+2 是源点和汇点。
 * @tparam Capacity type of flow. It is suggested to be integral number, but not real number.
 */
template<typename Capacity = uint64_t>
class Cinderella : public FlowNetwork<Capacity> {
    static constexpr Capacity veryBigConstant = std::numeric_limits<Capacity>::max() >> 19;
    static constexpr size_t getPairStudent(size_t index) { return ((index - 1) ^ 1) + 1; }
    size_t N, M;
    constexpr size_t getPairNodeFromStudent(size_t index) { return 2 * N + (index + 1) / 2; }

public:
    Cinderella(size_t N, size_t M) : N(N), M(M), FlowNetwork<Capacity>(2 * N + N + 2, M, 2 * N + N + 1, 2 * N + N + 2) {
        MyLog << "Initializing. (source, sink)=(" << this->source << ", " << this->sink << ")" << std::endl;
        MyLog << "Very big constant is " << veryBigConstant << std::endl;
    }
    /**
     * @param index For student index,
     * @param depressionC the "dance" choice would give him depressionC unhappiness
     * @param depressionD and "not to dance" choice would give him depressionD unhappiness
     * @param depressionE And if he chooses "dance" but his partner chooses "not to dance", he would receive depressionE unhappiness.
     */
    void setStudent(size_t index, Capacity depressionC, Capacity depressionD, Capacity depressionE) {
        MyLog << "Setting student " << index << " with depression (c,d,e)=(" << depressionC << ", " << depressionD << ", " << depressionE << ")" << std::endl;
        MyLog << "\taddEdge(" << this->source << ", " << index << ", " << depressionD + veryBigConstant << ") for d. " << std::endl;
        this->addEdge(this->source, index, depressionD + veryBigConstant);//割中与source在一起的是选了yes的。选了yes就没有depressionD。
        MyLog << "\taddEdge(" << index << ", " << getPairStudent(index) << ", " << depressionE << ") for e. " << std::endl;
        this->addEdge(index, getPairStudent(index), depressionE);
        MyLog << "\taddEdge(" << index << ", " << getPairNodeFromStudent(index) << ", " << depressionC + veryBigConstant << ") for c. " << std::endl;
        this->addEdge(index, getPairNodeFromStudent(index), depressionC + veryBigConstant);// 如果最终没有跳，就从这里加，否则从下面加。
        MyLog << "\tincreaseEdge(" << getPairNodeFromStudent(index) << ", " << this->sink << ", " << depressionC + veryBigConstant << ") for c. " << std::endl;
        this->increaseEdge(getPairNodeFromStudent(index), this->sink, depressionC + veryBigConstant);
    }
    /**
     * @param studentX  CC
     * @param studentY  LiDa Pu
     * @param depressionA If CC fails to dance with his partner at the final stage,
     * but LiDa Pu chooses "dance", CC would receive depressionA unhappiness;
     * @param depressionB If CC chooses "not to dance",
     * but LiDa Pu and his partner dance at the final stage, CC would receive depressionB unhappiness.
     */
    void addLoveLine(size_t studentX, size_t studentY, Capacity depressionA, Capacity depressionB) {
        MyLog << "Adding loveline " << studentX << " loves " << studentY << ", with depression (a,b)=(" << depressionA << ", " << depressionB << ")" << std::endl;
        MyLog << "\taddEdge(" << studentY << ", " << getPairNodeFromStudent(studentX) << ", " << depressionA << ") for a. " << std::endl;
        this->addEdge(studentY, getPairNodeFromStudent(studentX), depressionA);
        MyLog << "\taddEdge(" << studentX << ", " << getPairNodeFromStudent(studentY) << ", " << depressionB << ") for b. " << std::endl;
        this->addEdge(studentX, getPairNodeFromStudent(studentY), depressionB);
    }
    Capacity getMaximumFlow() override {
        return FlowNetwork<Capacity>::getMaximumFlow() - 2 * N * veryBigConstant;
    }
};
int main() {
    size_t N, M;
    std::cin >> N >> M;
    using Capacity = int64_t;
    Cinderella<Capacity> cinderella{N, M};
    for (size_t i = 1; i <= 2 * N; ++i) {
        Capacity c, d, e;
        std::cin >> c >> d >> e;
        cinderella.setStudent(i, c, d, e);
    }
    for (size_t i = 0; i < M; ++i) {
        size_t x, y;
        Capacity a, b;
        std::cin >> x >> y >> a >> b;
        cinderella.addLoveLine(x, y, a, b);
    }
    std::cout << cinderella.getMaximumFlow() << std::endl;
    return 0;
}