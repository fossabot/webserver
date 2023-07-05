#ifndef NGP_MMSS_CONNECTION_INITIATOR_H_
#define NGP_MMSS_CONNECTION_INITIATOR_H_

#include <string>
#include <vector>
#include <boost/function.hpp>
#include <boost/asio.hpp>

#include <mmss/Network/Network.h>

namespace NMMSS
{

// �������� ���������� ����������. ��������� ��������, ������� ����� ����������� � ����������� ������,
// �������� ���� �������� ��� �������. �� ��� ������ ������ ��������� TCP ����������, ������� ����
// ������, �� ������� ��� ������ ��������, �������� � �������� �����������, � ���� ��� ������, -
// ������ � ������ ������� �����, �� ������� ����� ������� ������������ �����.
class IConnectionInitiator
{
public:
    typedef boost::function1<void, NMMSS::PTCPSocket > FHandler;

    virtual ~IConnectionInitiator(){}

    virtual void InitiateConnection(const std::string& cookie,
        const std::vector<std::string>& addresses, unsigned short port,
        FHandler onConnected) =0;
    virtual void Cancel(const std::string& cookie) =0;
};

typedef boost::shared_ptr<IConnectionInitiator> PConnectionInitiator;
PConnectionInitiator GetConnectionInitiatorInstance();

}

#endif
