#include <iostream>
#include <vector>
#include <tuple>
#include <iterator>
#include <functional>
#include <algorithm>

struct Interval {
    int start, end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}

    bool operator<(const Interval & other) const {
        return std::make_tuple(start, end) < std::make_tuple(other.start, other.end);
    }

    bool overlapped(const Interval & other) {
        return std::max(start, other.start) < std::min(end, other.end);
    }

    std::ostream & output(std::ostream & os) const {
        os << "[" << start << "," << end << "]";
        return os;
    }
};

namespace std {
    template<>
    struct less<Interval> {
        bool operator() (const Interval & intv1, const Interval & intv2) {
            return intv1<intv2;
        }
    };
}

std::ostream & operator<<(std::ostream & os, const Interval & intv) {
    return intv.output(os);
}

class solution {
  public:
    std::vector<Interval> merge(const std::vector<Interval> & intvs) {
        auto cpy = intvs;
        std::sort(cpy.begin(), cpy.end());
        std::vector<Interval> result;
        result = mergeFunc(cpy);
        return result;
    }

  private:
    std::vector<Interval> mergeFunc(const std::vector<Interval> & vec) {
        std::vector<Interval> result;
        if (vec.empty())
            return result;
        else if (vec.size() == 1)
            result.push_back(vec[0]);
        else if (vec.size() > 1){
            auto first = vec[0], second = vec[1];
            if (first.overlapped(second)) {
                auto cpy = vec;
                cpy.erase(cpy.begin());
                cpy.erase(cpy.begin());
                cpy.insert(cpy.begin(), Interval(std::min(first.start,second.start), std::max(first.end, second.end)));
                result = mergeFunc(cpy);
            }
            else {
                auto cpy = vec;
                cpy.erase(cpy.begin());
                result = mergeFunc(cpy);
                result.insert(result.begin(), first);
            }
        }
        return result;
    }
};

int main() {
    std::vector<Interval> intvs{Interval(1,3), Interval(2,6), Interval(8,10), Interval(15,18)};

    solution soln;
    auto merged = soln.merge(intvs);
    std::copy(merged.begin(), merged.end(), std::ostream_iterator<Interval>(std::cout, " "));
    std::cout << std::endl;
}
