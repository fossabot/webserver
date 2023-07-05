#ifndef NGP_MMSS_CONNECTION_ACCEPTOR_H_
#define NGP_MMSS_CONNECTION_ACCEPTOR_H_

#include <string>
#include <chrono>
#include <boost/function.hpp>
#include <boost/asio.hpp>

#include <mmss/Network/Network.h>

namespace NMMSS
{

// ��������� ���� ���� �� LISTEN (���� �� ����-����-���� ����������� �� ������ � ���� ��������). 
// ����� ��, ��� ������� �������� ����������,
// ������������ ���� callback � ������� Register. �������� �������� �� ������ �� cookie - ���
// ������, ������� ������ ������ ��������� � ���������� ������. ���� ���������� ������ � ��
// ������ ������� - ���������� ������� �����������. ���� ����������� ���������� �������, - 
// ���������� ������ onAccepted, � ������� ���������� �������, ��� �������� �����,
// �� ������� ����� ������� ������������ �����.
class ITcpConnectionAcceptor
{
public:
    typedef boost::function1<void, PTCPSocket > FHandler;
    typedef std::chrono::milliseconds TDuration;
    
    virtual ~ITcpConnectionAcceptor(){}

    virtual unsigned short GetPort() =0;
    virtual void Register(const std::string& cookie, FHandler onAccepted, TDuration timeout) =0;
    virtual void Cancel(const std::string& cookie) =0;
};

typedef boost::shared_ptr<ITcpConnectionAcceptor> PTCPConnectionAcceptor;
PTCPConnectionAcceptor GetTcpConnectionAcceptorInstance(NCorbaHelpers::PReactor reactor);

class IUdpConnectionAcceptor
{
public:

    virtual ~IUdpConnectionAcceptor() { }

    virtual PUDPSocket CreateUdpSocket(const std::string&) = 0;
};

typedef boost::shared_ptr<IUdpConnectionAcceptor> PUDPConnectionAcceptor;
PUDPConnectionAcceptor GetUdpConnectionAcceptorInstance();

}

#endif
