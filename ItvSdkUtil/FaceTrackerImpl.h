#ifndef _FACETRACKERIMPL_H_
#define _FACETRACKERIMPL_H_

#include "FaceTracker.h"
#include <deque>
#include <set>

typedef std::pair<ITV8::timestamp_t, ITV8::RectangleF> trackInfo_t;

class CFaceTracker:	public IFaceTracker
{
private:
    typedef std::vector<ITV8::RectangleF> rectanglesList_t;
    typedef rectanglesList_t::size_type rectangleIndex_t;

	//�����, ����� ������� ���� ��������� ���������� 
	// � �������������
	static const ITV8::uint64_t m_timeoutTime = 1500;

	// ����������, � �������� �������� ����������� ����� ����, � �� ������������� � ��� ���������
	const ITV8::double_t m_distNewTrack;

	// ����������� �������� � ������� �����, ������� ������������ ��� �������� �����.
	// �������, ���� ���� ��������� �� �������, �����, ��� m_coeffNearness*���_�������_������ � 
	// ���������� �� ����� ����� �� �������� �� ������ �����, �� ��������� ����.
	const ITV8::double_t m_coeffNearness;

	// ������ � ������ ������������ ������
	ITV8::int32_t m_frameWidth, m_frameHeight;

	// ��������� ������ �� ����� ������������, ������������ � ������� �������
	// �������� � ��������������� ������� - ����� ��������� ����, ��������� � ������
	std::map<ITV8::uint64_t, std::deque<trackInfo_t> > m_allTracks;	

    // ��������� ����������� ������, �������������� �� �������� � m_allTracks
    std::map<ITV8::uint64_t, std::deque<trackInfo_t> > m_appTracks;	

    // ��������� ����������� ������, �������������� �� �������� � m_allTracks
    std::map<ITV8::uint64_t, std::deque<trackInfo_t> > m_disappTracks;	

	// ��������� ���������� ID, ���������� �� 0
	ITV8::uint64_t m_lastID;

	// ������� ���������� ����������� ����� �������������
	ITV8::PointF CalcRectCenter(const ITV8::RectangleF& r);

	// ������� ���������� ���������� ����� ����� �������
	ITV8::double_t CalcDistBetweenPoints(const ITV8::PointF& p1, const ITV8::PointF& p2);

	// ������� ���������� �������� ���� ����� �������� (p1, p2) � (p2, p3)
	ITV8::double_t CalcCosAngleBetweenVectors(const ITV8::PointF& p1, const ITV8::PointF &p2, const ITV8::PointF &p3);

	// ������� ����������� ���������� ����� ����������������
	ITV8::double_t CalcDistBetweenRects(const ITV8::RectangleF& r1, const ITV8::RectangleF& r2);

	// ������� �������� �� ������� ��������������� ������� ���������������
	void RemoveCloseRects(std::vector<ITV8::RectangleF>& rects);

	// ������� ������������ ��������� ������� �� 2� ������ � ������ ������� tx
	// ����� ���������� � ������� ����������
	ITV8::PointF PredictPosition(const ITV8::timestamp_t& t1, const ITV8::PointF& p1, 
								const ITV8::timestamp_t& t2, const ITV8::PointF& p2,
								const ITV8::timestamp_t& tx);

	// ������� ������������ ��������� ������� �� 3� ������ � ������ ������� tx
	// ����� ���������� � ������� ����������
	ITV8::PointF PredictPosition(const ITV8::timestamp_t& t1, const ITV8::PointF& p1, 
								const ITV8::timestamp_t& t2, const ITV8::PointF& p2,
								const ITV8::timestamp_t& t3, const ITV8::PointF& p3,
								const ITV8::timestamp_t& tx);

	// ������� ���������� ���������, ��� ���������� "��������" ��������
	void getDispersion(std::deque<trackInfo_t> &info, double &dispX, double &dispY);

	// ������� ���������� ��������� ��� �������������� ���������� �������
	void leastSquareFunction(std::deque<trackInfo_t> &info, 
						     ITV8::double_t &x0, ITV8::double_t &vx, ITV8::double_t &ax,
							 ITV8::double_t &y0, ITV8::double_t &vy, ITV8::double_t &ay);

    typedef std::multimap<ITV8::double_t, std::pair<ITV8::uint64_t, rectangleIndex_t> > distancesMap_t;
    typedef std::set<rectangleIndex_t> rectangleIndexesSet_t;

	// ������� ����������� ��������������� � ����������� �� ������ ����� ����������
    void FillTrajectsMap(distancesMap_t& distancesMap,
                         rectangleIndexesSet_t& rectsSet, std::set<ITV8::uint64_t>& trajectsSet,
						 const std::vector<ITV8::RectangleF>& rects, const ITV8::timestamp_t& frameTime,
						 std::map<ITV8::uint64_t, std::deque<trackInfo_t> >& allTracks);

	// ������� �������� ������ �� ���������� ������, ���������� � ������� �� ����������� ���������� �����
	void DeleteOldTracks(const ITV8::timestamp_t& frameTime, std::set<ITV8::uint64_t>& trajectsSet,
						 const std::map<ITV8::uint64_t, ITV8::double_t>& borderDistances);

	// ������� �������� ������ ������ �� ������ ������� ���������������
    void CreateNewTracks(const ITV8::timestamp_t& frameTime, std::set<rectangleIndex_t>& rectsSet,
						const std::vector<ITV8::RectangleF>& rects);

    //// ������� ���������� �������� ���� ���������������
    //bool closenessEval(ITV8::RectangleF &r1, ITV8::RectangleF &r2);

public:
	CFaceTracker();
	// ����� ���������� � �������������
	void OnFrame(const ITV8::timestamp_t& frameTime, const std::vector<ITV8::RectangleF>& rects);
	void GetCurrentTracks(std::map<ITV8::uint64_t, ITV8::RectangleF>& appearedTracks,
                          std::map<ITV8::uint64_t, ITV8::RectangleF>& currentTracks,
                          std::map<ITV8::uint64_t, ITV8::RectangleF>& disappearedTracks);
	void ForceFinishTracks(std::map<ITV8::uint64_t, ITV8::RectangleF>& disappearedTracks);

	~CFaceTracker();
};

IFaceTracker* CreateTracker()
{
	return new CFaceTracker();
}

#endif