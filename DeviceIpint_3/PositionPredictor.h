#include <boost/cstdint.hpp>
#include <boost/date_time.hpp>
#include <boost/thread/thread.hpp>

#include <Logging/log2.h>

#ifdef BOOST_NO_CXX11_CONSTEXPR
const
#else
constexpr
#endif
static boost::chrono::seconds minimalTrackDurationForPredictionInFullCamDelay{ 2 };
class CPositionPredictor
{
private:
	struct SObjectInfo
	{
		// ������� ��������� �������.
		double position;

		// ����� "������", � ������� ��� ������� ���� �������������
		boost::posix_time::ptime camTime;

		// ����� "����������", � ������� ��� ������� ���� �������� �� ������.
		// ������ ���� ��������� ��� ���������� ������������ ��� ������ "� ���������� �����������".
		boost::posix_time::ptime localTime;

		SObjectInfo(double const& position_, 
					boost::posix_time::ptime const& camTime_,
					boost::posix_time::ptime const& localTime_)
		:	position(position_)
		,	camTime(camTime_)
		,	localTime(localTime_)
		{}
	};
	
	// ��������� x-���������� ������
	std::map<boost::uint32_t, std::vector<SObjectInfo> > m_TracksContainerX;

	// ��������� y-���������� ������
	std::map<boost::uint32_t, std::vector<SObjectInfo> > m_TracksContainerY;

	// �������� ������
	boost::posix_time::time_duration m_CamDelay;

	// ������� ������� ������ ��� ��� ����������� x(t) = x0 + v*t + a * t * t / 2
	void leastSquareFunction(std::vector<SObjectInfo> &info, double &x0, double &v, double &a);

    DECLARE_LOGGER_HOLDER;
public:
	// � ������������ �������� � ���, ������ �������� ������ (� �������������)
	CPositionPredictor(DECLARE_LOGGER_ARG, const boost::posix_time::time_duration &camDelay);
	
	// ���� �������� �� ��������, �� ������� �� �������
	CPositionPredictor(DECLARE_LOGGER_ARG);
	~CPositionPredictor();

	// ������� ���������� ������� ����� � ������� ���������
	// id - ������������� �����
	// position - ���������� ������ ����������� ����� �������
	// time - �������������� ���������� ������� �����
	void AddObjectPosition(const boost::uint32_t id, 
						   const std::pair<double, double> &position, 
						   const boost::posix_time::ptime &time);

	// ������� �������� ����� � �������� id �� ���������
	// id - ������������� �����
	void EraseObject(const boost::uint32_t id);

	// ������� ������������� �����������
	// id - ������������� �����, ��� �������� ����� �������������� �����������
	// predictedPosition - ������������� �������
	// ����������� �������� - ����� ��� �������
	enum EPrediction {eSuccess, eFail};
	EPrediction DoPrediction(const boost::uint32_t id, 
							 std::pair<double, double> &predictedPosition);
};
