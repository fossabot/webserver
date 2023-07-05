#ifndef ITVSDKUTIL_FACETRACKER_H
#define ITVSDKUTIL_FACETRACKER_H

#include <ItvSdk/include/baseTypes.h>
#include <vector>
#include <map>

class IFaceTracker
{
public:
    // � ������� ���������� ����� ������������� �������.
    // ������ ��������� �� ������ �����, ��� ����������� �� ����
    // ����������, ��� �� �� ������� ����� ��� ���.
    // rects - ������ ���������������
    // frameTime - ������� ����� � �������������
    virtual void OnFrame(const ITV8::timestamp_t& frameTime, const std::vector<ITV8::RectangleF>& rects) = 0;    

    // appearedTracks - ������ ����������� ������ � id
    // currentTracks - ������ ������ ������ � id
    // disappearedTracks - ������ ����������� ������
    // � �������� ���������� ������� ���������� ���������� ������, � ��� �� ���� �����
    virtual void GetCurrentTracks(std::map<ITV8::uint64_t, ITV8::RectangleF>& appearedTracks,
                                  std::map<ITV8::uint64_t, ITV8::RectangleF>& currentTracks,
                                  std::map<ITV8::uint64_t, ITV8::RectangleF>& disappearedTracks) = 0;

    // ������� "���������� ����������" ���� ��������� ������, � ����������� �� � �������� �����������
    virtual void ForceFinishTracks(std::map<ITV8::uint64_t, ITV8::RectangleF>& disappearedTracks) = 0;

    virtual ~IFaceTracker() {}
};

// ������� ��������� ��������� �������
// � ������� ���������� ������-������ �����, �� ������� ���������� �������������.
IFaceTracker* CreateTracker();

#endif // ITVSDKUTIL_FACETRACKER_H
