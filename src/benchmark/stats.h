#ifndef STATS_H
#define STATS_H

class Stats
{
public:
    Stats(double mean = 0.0, double min = 0.0, double max = 0.0)
        : mean_time(mean), min_time(min), max_time(max) {}

    double mean() const { return mean_time; }
    double min() const { return min_time; }
    double max() const { return max_time; }

private:
    double mean_time;
    double min_time;
    double max_time;
};

#endif