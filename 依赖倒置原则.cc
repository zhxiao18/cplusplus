#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

class BankWorker
{
public:
    virtual void doBusiness() = 0;
    virtual ~BankWorker() {}
};

class SaveBankWorker
: public BankWorker
{
public:
    void doBusiness() override
    {
        cout << "办理存款业务" << endl;
    }
};

class PayBankWorker
: public BankWorker
{
public:
    void doBusiness() override
    {
        cout << "办理支付业务" << endl;
    }
};

class TransferBankWorker
: public BankWorker
{
public:
    void doBusiness() override
    {
        cout << "办理转账业务" << endl;
    }
};

void doBusiness(BankWorker *worker)
{
    worker->doBusiness();
}

void test()
{
    unique_ptr<BankWorker> saveWorker(new SaveBankWorker());
    unique_ptr<BankWorker> payWorker(new PayBankWorker());
    unique_ptr<BankWorker> transferWorker(new TransferBankWorker());

    doBusiness(saveWorker.get());
    doBusiness(payWorker.get());
    doBusiness(transferWorker.get());
}

int main(int argc, char **argv)
{
    test();
    return 0;
}


