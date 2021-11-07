#ifndef UNITTESTS_H
#define UNITTESTS_H

#include <vector>
#include <QPair>
#include <QtDebug>
#include <repository/vector_impl/cardrepositoryvectorimpl.h>
#include <repository/vector_impl/transactionrepositoryvectorimpl.h>
#include <repository/vector_impl/userrepositoryvectorimpl.h>
#include <util/utils.h>
#include <service/cardservice.h>
#include <service/transactionservice.h>

using namespace std;

class UnitTests
{
public:
    UnitTests();
    void runTests();
    bool shouldSuccessfullyCreateNewUser();
    bool shouldCreateLinkCardsToUser();
    bool shouldMakeTransactionsWithoutReserveCard();
    bool shouldMakeTransactionsWithReserveCard();
    bool shouldMakeTransactionsWithMultipleReserveCards();
private:
    vector<QPair<QString,bool>> _testResults;
    UserRepository *userRepository;
    CardRepository *cardRepository;
    TransactionRepository *transactionRepository;
    CardService *cardService;
    TransactionService *transactionService;

};
#endif // UNITTESTS_H
