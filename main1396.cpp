//1396. 设计地铁系统

#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class UndergroundSystem {
public:
    UndergroundSystem() {
        //思路：重点是如何存储数据，进站口和出站口和id才能标识一趟行程
        //未完成的行程，用id为key记录，而完成的行程用进站口和出站口字符串拼接为key，时间为value
        
    }
    
    void checkIn(int id, string stationName, int t) {
        unfinishedItinerary_[id] = {stationName,t};
    }
    
    void checkOut(int id, string stationName, int t) {
        string itinerary = unfinishedItinerary_[id].first + stationName;
        finishedItinerary_[itinerary].push_back(t - unfinishedItinerary_[id].second);
    }
    
    double getAverageTime(string startStation, string endStation) {
        string itinerary = startStation + endStation;
        if(finishedItinerary_[itinerary].empty())
        {
            return 0.0;
        }
        int sum =0;
        for(auto t : finishedItinerary_[itinerary])
        {
            sum += t;
        }

        return (double)sum / finishedItinerary_[itinerary].size();
    }

    unordered_map<int,pair<string,int>> unfinishedItinerary_;
    unordered_map<string,vector<int>> finishedItinerary_;
};

int main()
{
    UndergroundSystem undergroundSystem;
    undergroundSystem.checkIn(45, "Leyton", 3);
    undergroundSystem.checkIn(32, "Paradise", 8);
    undergroundSystem.checkIn(27, "Leyton", 10);
    undergroundSystem.checkOut(45, "Waterloo", 15);
    undergroundSystem.checkOut(27, "Waterloo", 20);
    undergroundSystem.checkOut(32, "Cambridge", 22);
    printf("%f\n",undergroundSystem.getAverageTime("Paradise", "Cambridge")); //14.0

    printf("%f\n",undergroundSystem.getAverageTime("Leyton", "Waterloo"));  //11.0
    undergroundSystem.checkIn(10, "Leyton", 24);
    printf("%f\n",undergroundSystem.getAverageTime("Leyton", "Waterloo")); //11.0
    undergroundSystem.checkOut(10, "Waterloo", 38);
    printf("%f\n",undergroundSystem.getAverageTime("Leyton", "Waterloo")); //12.0

    return 0;

}