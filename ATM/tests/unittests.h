#ifndef UNITTESTS_H
#define UNITTESTS_H

#include <vector>
#include <QPair>
#include <QtDebug>
#include <repository/vector_impl/automatictransactionrepositoryvectorimpl.h>
#include <repository/vector_impl/cardrepositoryvectorimpl.h>
#include <repository/vector_impl/transactionrepositoryvectorimpl.h>
#include <repository/vector_impl/userrepositoryvectorimpl.h>
#include <util/utils.h>
#include <service/automatictransactionservice.h>
#include <service/cardservice.h>
#include <service/transactionservice.h>
#include <QThread>

using namespace std;

class UnitTests
{
public:
    UnitTests();
    void runTests();
private:
    bool shouldSuccessfullyCreateNewUser();
    bool shouldCreateLinkCardsToUser();
    bool shouldMakeTransactionsWithoutReserveCard();
    bool shouldMakeTransactionsWithReserveCard();
    bool shouldMakeTransactionsWithMultipleReserveCards();
    bool shouldNotAllowTransaction();
    bool shouldNotAllowTransactionWithReserveCard();
    bool shouldNotAllowTransactionWithoutReserveCard();
    bool shouldNotAllowTransactionWithMultipleReserveCards();
    bool shouldMakeAutomaticTransaction();
    bool shouldMakeAutomaticTransactionWithOddParts();
    bool shouldMakeAutomaticTransactionWithOddPartsAndReserveCards();
    bool shouldMakeFirstPartOfAutomaticTransaction();
    bool shouldFailAutomaticTransaction();

    bool throwsCircularDependencyException();
    bool throwsIncorrectCardAuthException();
    bool throwsNotFoundException();
    bool throwsLogicConflictException();
    bool throwsLogicConflictExceptionOverflow();
    
    vector<QPair<QString,bool>> _testResults;
    UserRepository *_userRepository;
    CardRepository *_cardRepository;
    TransactionRepository *_transactionRepository;
    AutomaticTransactionRepository *_automaticTransactionRepository;
    CardService *_cardService;
    TransactionService *_transactionService;
    AutomaticTransactionService *_automaticTransactionService;

};
#endif // UNITTESTS_H
