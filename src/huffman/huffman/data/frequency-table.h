#ifndef FREQUENCY_TABLE_H
#define FREQUENCY_TABLE_H
#include <unordered_map>
#include <vector>

namespace data
{
    template<typename T>
    class FrequencyTable
    {
    private:

        std::unordered_map<T, unsigned long long> frequencies_data;

    public:

        unsigned long long operator[](const T& x) const
        {
            auto result = frequencies_data.find(x);
            if (result == frequencies_data.end()) {
                return 0;
            }
            else {
                return result->second;
            }
        }

        void increment(const T& x)
        {
            ++frequencies_data[x];
        }

        std::vector<T> values() const
        {
            std::vector<T> result;
            result.reserve(frequencies_data.size());

            for (auto it = frequencies_data.begin(); it != frequencies_data.end(); ++it) {
                result.push_back(it->first);
            }

            return result;
        }
    };

    template<typename T>
    FrequencyTable<T> count_frequencies(const std::vector<T>& values)
    {
        FrequencyTable<T> frequencies;
        for (const auto& value : values) {
            frequencies.increment(value);
        }
        return frequencies;
    }
}

#endif