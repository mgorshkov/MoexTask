#pragma once

#include <string>
#include <memory>
#include <queue>
#include <vector>

struct Data
{
    Data(const std::string& aEvent, int aAvgTsMr)
        : mEvent(aEvent)
        , mAvgTsMr(aAvgTsMr)
    {
    }
    std::string mEvent;
    int mAvgTsMr;
};

using DataPtr = std::unique_ptr<Data>;
using DataQueue = std::queue<DataPtr>;

using Log = std::vector<DataPtr>;

struct Statistics
{
    int mMin; // min � ����������� ����� ������ �� ���������� � �������������
    int mMedian; // - 50% - �������
    int m90; // - 90% - 90% ����������� ������ 122 �����������
    int m99; // - 99% - 99% ����������� ������ 140 �����������
    int m999; // - 99.9% - 99.9% ����������� ������ 145 �����������
};


