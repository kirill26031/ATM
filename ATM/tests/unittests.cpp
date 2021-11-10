#include "unittests.h"




UnitTests::UnitTests()
{
    _userRepository = UserRepositoryVectorImpl::getInstance();
    _cardRepository = CardRepositoryVectorImpl::getInstance();
    _transactionRepository = TransactionRepositoryVectorImpl::getInstance();
    _automaticTransactionRepository = AutomaticTransactionRepositoryVectorImpl::getInstance();
    _cardService  = CardService::getInstance();
    _transactionService  = TransactionService::getInstance();
    _automaticTransactionService  = AutomaticTransactionService::getInstance();

}

void UnitTests::runTests()
{
    qDebug() << "======RUNNING TESTS=======";

    _testResults.push_back(qMakePair("shouldSuccessfullyCreateNewUser", shouldSuccessfullyCreateNewUser()));
    _testResults.push_back(qMakePair("shouldCreateLinkCardsToUser", shouldCreateLinkCardsToUser()));
    _testResults.push_back(qMakePair("shouldMakeTransactionsWithoutReserveCard", shouldMakeTransactionsWithoutReserveCard()));
    _testResults.push_back(qMakePair("shouldMakeTransactionsWithReserveCard", shouldMakeTransactionsWithReserveCard()));
    _testResults.push_back(qMakePair("shouldMakeTransactionsWithMultipleReserveCards", shouldMakeTransactionsWithMultipleReserveCards()));
    _testResults.push_back(qMakePair("shouldNotAllowTransaction", shouldNotAllowTransaction()));
    _testResults.push_back(qMakePair("shouldNotAllowTransactionWithReserveCard", shouldNotAllowTransactionWithReserveCard()));
    _testResults.push_back(qMakePair("shouldNotAllowTransactionWithoutReserveCard", shouldNotAllowTransactionWithoutReserveCard()));
    _testResults.push_back(qMakePair("shouldNotAllowTransactionWithMultipleReserveCards", shouldNotAllowTransactionWithMultipleReserveCards()));
    _testResults.push_back(qMakePair("shouldMakeAutomaticTransaction", shouldMakeAutomaticTransaction()));
    _testResults.push_back(qMakePair("shouldMakeAutomaticTransactionWithOddParts", shouldMakeAutomaticTransactionWithOddParts()));
    _testResults.push_back(qMakePair("shouldMakeAutomaticTransactionWithOddPartsAndReserveCards", shouldMakeAutomaticTransactionWithOddPartsAndReserveCards()));
    _testResults.push_back(qMakePair("shouldMakeFirstPartOfAutomaticTransaction", shouldMakeFirstPartOfAutomaticTransaction()));
    _testResults.push_back(qMakePair("shouldFailAutomaticTransaction", shouldFailAutomaticTransaction()));

    _testResults.push_back(qMakePair("throwsCircularDependencyException", throwsCircularDependencyException()));
    _testResults.push_back(qMakePair("throwsIncorrectCardAuthException", throwsIncorrectCardAuthException()));
    _testResults.push_back(qMakePair("throwsNotFoundException", throwsNotFoundException()));
    _testResults.push_back(qMakePair("throwsLogicConflictException", throwsLogicConflictException()));
    _testResults.push_back(qMakePair("throwsLogicConflictExceptionOverflow", throwsLogicConflictExceptionOverflow()));


    qDebug() << "======TEST RESULTS=======";


    int failedTests = 0;
    int passedTests = 0;
    for (auto&& test: _testResults){
        QString outcome;
        if (test.second){
            passedTests++;
            outcome = "SUCCESS";
        }
        else {
            failedTests++;
            outcome = "FAILED";
        }

        qDebug().noquote() << test.first << " : " << outcome;
    }
    qDebug() << "total: " << _testResults.size() << ", success: " << passedTests << ", failed: " << failedTests;
    qDebug() << "======TESTS FINISHED=======";

    //clear up

    _userRepository->clearAll();
    _transactionRepository->clearAll();
    _automaticTransactionRepository->clearAll();
    _cardRepository->clearAll();


}

bool UnitTests::shouldSuccessfullyCreateNewUser()
{
    UserEntity firstUser = UserEntity(generateId(), "Bob Bobber");
    UserEntity secondUser = UserEntity(generateId(), "Sam Sammer");
    _userRepository->setById(firstUser.id(), firstUser);
    _userRepository->setById(secondUser.id(), secondUser);
    if(_userRepository->existsById(firstUser.id()) && _userRepository->existsById(secondUser.id())){
        string names = _userRepository->getById(firstUser.id()).name() + ", "
                + _userRepository->getById(secondUser.id()).name();
        qDebug().noquote() <<  "[" << __func__<< "]" << QString::fromStdString(names);
        return true;
    }
    else
        return false;
}

bool UnitTests::shouldCreateLinkCardsToUser()
{
    UserEntity firstUser = UserEntity(generateId(), "Kek Kekker");
    UserEntity secondUser = UserEntity(generateId(), "Tom Tommer");
    _userRepository->setById(firstUser.id(), firstUser);
    _userRepository->setById(secondUser.id(), secondUser);

    long firstCard = _cardService->generateCard(firstUser.id(), firstUser.name());
    long secondCard = _cardService->generateCard(secondUser.id(), secondUser.name());
    long thirdCard = _cardService->generateCard(secondUser.id(), secondUser.name());
    _cardService->setAsReserveCard(_cardService->getCardById(secondCard).cardId(),
                                   _cardService->getCardById(thirdCard).cardId(), 0);
    qDebug().noquote() <<  "[" << __func__<< "]" << _cardService->getCardById(firstCard).pin();
    qDebug().noquote() <<  "[" << __func__<< "]" << _cardService->getCardById(secondCard).pin();
    qDebug().noquote() <<  "[" << __func__<< "]" << _cardService->getCardById(thirdCard).pin();

    bool condition1 = _cardService->getCardById(firstCard).id() == firstCard;
    bool condition2 = _cardService->getCardById(secondCard).id() == secondCard;
    bool condition3 = _cardService->getCardById(secondCard).balance() == 0;
    bool condition4 = *(_cardService->getCardById(secondCard).reserveCardId()) == thirdCard;

    return condition1 && condition2 && condition3 && condition4;


}

bool UnitTests::shouldMakeTransactionsWithoutReserveCard()
{
    UserEntity firstUser = UserEntity(generateId(), "Test Tester");
    UserEntity secondUser = UserEntity(generateId(), "Cooc Coocer");
    _userRepository->setById(firstUser.id(), firstUser);
    _userRepository->setById(secondUser.id(), secondUser);

    CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),1000);
    _cardRepository->setById(firstCard.id(),firstCard );

    CardEntity secondCard(generateId(), generateCardId(), generatePin(),secondUser.id(),secondUser.name(),0);
    _cardRepository->setById(secondCard.id(),secondCard );


    _transactionService->Transfer(500, firstCard.id(),secondCard.id());

    bool condition1 = _cardService->getCardById(firstCard.id()).balance() == 500;
    bool condition2 = _cardService->getCardById(secondCard.id()).balance() == 500;

    return condition1 && condition2;

}

bool UnitTests::shouldMakeTransactionsWithReserveCard()
{
    UserEntity firstUser = UserEntity(generateId(), "New Newer");
    UserEntity secondUser = UserEntity(generateId(), "Old Older");
    _userRepository->setById(firstUser.id(), firstUser);
    _userRepository->setById(secondUser.id(), secondUser);

    CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),300);
    CardEntity secondCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),500);
    _cardRepository->setById(firstCard.id(),firstCard );
    _cardRepository->setById(secondCard.id(),secondCard );
    _cardService->setAsReserveCard(_cardService->getCardById(firstCard.id()).cardId(),
                                   _cardService->getCardById(secondCard.id()).cardId(), 0);

    CardEntity thirdCard(generateId(), generateCardId(), generatePin(),secondUser.id(),secondUser.name(),0);
    _cardRepository->setById(thirdCard.id(),thirdCard );


    bool condition4 = _transactionService->Transfer(500, firstCard.id(), thirdCard.id());

    qDebug().noquote() <<  "[" << __func__<< "]" << "FROM card balance" << _cardService->getCardById(firstCard.id()).balance();
    qDebug().noquote() <<  "[" << __func__<< "]" << "RESERVE card balance" <<  _cardService->getCardById(secondCard.id()).balance();
    qDebug().noquote() <<  "[" << __func__<< "]" << "TO card balance" <<  _cardService->getCardById(thirdCard.id()).balance();
    qDebug().noquote() <<  "[" << __func__<< "]" << "Can Transfer" <<  condition4;


    bool condition1 = _cardService->getCardById(firstCard.id()).balance() == 0;
    bool condition2 = _cardService->getCardById(secondCard.id()).balance() == 300;
    bool condition3 = _cardService->getCardById(thirdCard.id()).balance() == 500;

    return condition1 && condition2 && condition3 && condition4;

}

bool UnitTests::shouldMakeTransactionsWithMultipleReserveCards()
{
    UserEntity firstUser = UserEntity(generateId(), "Will Willer");
    UserEntity secondUser = UserEntity(generateId(), "Sonya Sonyer");
    _userRepository->setById(firstUser.id(), firstUser);
    _userRepository->setById(secondUser.id(), secondUser);

    CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),500);
    CardEntity secondCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),300);
    CardEntity thirdCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),200);
    CardEntity fourthCard(generateId(), generateCardId(), generatePin(),secondUser.id(),secondUser.name(),0);
    _cardRepository->setById(firstCard.id(),firstCard );
    _cardRepository->setById(secondCard.id(),secondCard );
    _cardRepository->setById(thirdCard.id(),thirdCard );
    _cardRepository->setById(fourthCard.id(),fourthCard );

    _cardService->setAsReserveCard(_cardService->getCardById(firstCard.id()).cardId(),
                                   _cardService->getCardById(secondCard.id()).cardId(), 0);

    _cardService->setAsReserveCard(_cardService->getCardById(secondCard.id()).cardId(),
                                   _cardService->getCardById(thirdCard.id()).cardId(), 0);


    bool condition4 = _transactionService->Transfer(900, firstCard.id(), fourthCard.id());

    qDebug().noquote() <<  "[" << __func__<< "]" << "FROM card balance" << _cardService->getCardById(firstCard.id()).balance();
    qDebug().noquote() <<  "[" << __func__<< "]" << "RESERVE card balance" <<  _cardService->getCardById(secondCard.id()).balance();
    qDebug().noquote() <<  "[" << __func__<< "]" << "TO card balance" <<  _cardService->getCardById(thirdCard.id()).balance();
    qDebug().noquote() <<  "[" << __func__<< "]" << "Can Transfer" <<  condition4;


    bool condition1 = _cardService->getCardById(firstCard.id()).balance() == 0;
    bool condition2 = _cardService->getCardById(secondCard.id()).balance() == 0;
    bool condition3 = _cardService->getCardById(thirdCard.id()).balance() == 100;
    bool condition5 = _cardService->getCardById(fourthCard.id()).balance() == 900;

    return condition1 && condition2 && condition3 && condition4 && condition5;

}

bool UnitTests::shouldNotAllowTransaction()
{
    UserEntity firstUser = UserEntity(generateId(), "Hugh Hugher");
    UserEntity secondUser = UserEntity(generateId(), "John Johner");
    _userRepository->setById(firstUser.id(), firstUser);
    _userRepository->setById(secondUser.id(), secondUser);

    CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),200);
    CardEntity secondCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),500);
    _cardRepository->setById(firstCard.id(),firstCard );
    _cardRepository->setById(secondCard.id(),secondCard );

    bool condition1 = _transactionService->Transfer(300, firstCard.id(), secondCard.id());

    qDebug().noquote() <<  "[" << __func__<< "]" << "FROM card balance" << _cardService->getCardById(firstCard.id()).balance();
    qDebug().noquote() <<  "[" << __func__<< "]" << "TO card balance" <<  _cardService->getCardById(secondCard.id()).balance();
    qDebug().noquote() <<  "[" << __func__<< "]" << "Can Transfer" <<  condition1;


    bool condition2 = _cardService->getCardById(firstCard.id()).balance() == 200;
    bool condition3 = _cardService->getCardById(secondCard.id()).balance() == 500;

    return !condition1 && condition2 && condition3;

}

bool UnitTests::shouldNotAllowTransactionWithReserveCard()
{
    UserEntity firstUser = UserEntity(generateId(), "Hill Hiller");
    UserEntity secondUser = UserEntity(generateId(), "Yui Yuier");
    _userRepository->setById(firstUser.id(), firstUser);
    _userRepository->setById(secondUser.id(), secondUser);

    CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),200);
    CardEntity secondCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),200);
    CardEntity thirdCard(generateId(), generateCardId(), generatePin(),secondUser.id(),secondUser.name(),500);

    _cardRepository->setById(firstCard.id(),firstCard );
    _cardRepository->setById(secondCard.id(),secondCard );
    _cardRepository->setById(thirdCard.id(),thirdCard );

    _cardService->setAsReserveCard(_cardService->getCardById(firstCard.id()).cardId(),
                                   _cardService->getCardById(secondCard.id()).cardId(), 100);

    bool condition1 = _transactionService->Transfer(400, firstCard.id(), thirdCard.id());

    qDebug().noquote() <<  "[" << __func__<< "]" << "FROM card balance" << _cardService->getCardById(firstCard.id()).balance();
    qDebug().noquote() <<  "[" << __func__<< "]" << "TO card balance" <<  _cardService->getCardById(secondCard.id()).balance();
    qDebug().noquote() <<  "[" << __func__<< "]" << "Can Transfer" <<  condition1;


    bool condition2 = _cardService->getCardById(firstCard.id()).balance() == 200;
    bool condition3 = _cardService->getCardById(secondCard.id()).balance() == 200;
    bool condition4 = _cardService->getCardById(thirdCard.id()).balance() == 500;

    return !condition1 && condition2 && condition3 && condition4;

}

bool UnitTests::shouldNotAllowTransactionWithoutReserveCard()
{
    UserEntity firstUser = UserEntity(generateId(), "Des Deser");
    UserEntity secondUser = UserEntity(generateId(), "Con Coner");
    _userRepository->setById(firstUser.id(), firstUser);
    _userRepository->setById(secondUser.id(), secondUser);

    CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),500);
    CardEntity secondCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),200);
    CardEntity thirdCard(generateId(), generateCardId(), generatePin(),secondUser.id(),secondUser.name(),200);

    _cardRepository->setById(firstCard.id(),firstCard );
    _cardRepository->setById(secondCard.id(),secondCard );
    _cardRepository->setById(thirdCard.id(),thirdCard );

    bool condition1 = _transactionService->Transfer(600, firstCard.id(), thirdCard.id());

    qDebug().noquote() <<  "[" << __func__<< "]" << "FROM card balance" << _cardService->getCardById(firstCard.id()).balance();
    qDebug().noquote() <<  "[" << __func__<< "]" << "TO card balance" <<  _cardService->getCardById(secondCard.id()).balance();
    qDebug().noquote() <<  "[" << __func__<< "]" << "Can Transfer" <<  condition1;


    bool condition2 = _cardService->getCardById(firstCard.id()).balance() == 500;
    bool condition3 = _cardService->getCardById(secondCard.id()).balance() == 200;
    bool condition4 = _cardService->getCardById(thirdCard.id()).balance() == 200;

    return !condition1 && condition2 && condition3 && condition4;

}

bool UnitTests::shouldNotAllowTransactionWithMultipleReserveCards()
{
    UserEntity firstUser = UserEntity(generateId(), "Will Willer");
    UserEntity secondUser = UserEntity(generateId(), "Sonya Sonyer");
    _userRepository->setById(firstUser.id(), firstUser);
    _userRepository->setById(secondUser.id(), secondUser);

    CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),100);
    CardEntity secondCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),400);
    CardEntity thirdCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),500);
    CardEntity fourthCard(generateId(), generateCardId(), generatePin(),secondUser.id(),secondUser.name(),0);
    _cardRepository->setById(firstCard.id(),firstCard );
    _cardRepository->setById(secondCard.id(),secondCard );
    _cardRepository->setById(thirdCard.id(),thirdCard );
    _cardRepository->setById(fourthCard.id(),fourthCard );

    _cardService->setAsReserveCard(_cardService->getCardById(firstCard.id()).cardId(),
                                   _cardService->getCardById(secondCard.id()).cardId(), 0);

    _cardService->setAsReserveCard(_cardService->getCardById(secondCard.id()).cardId(),
                                   _cardService->getCardById(thirdCard.id()).cardId(), 0);


    bool condition4 = _transactionService->Transfer(1001, firstCard.id(), fourthCard.id());

    qDebug().noquote() <<  "[" << __func__<< "]" << "FROM card balance" << _cardService->getCardById(firstCard.id()).balance();
    qDebug().noquote() <<  "[" << __func__<< "]" << "RESERVE card balance" <<  _cardService->getCardById(secondCard.id()).balance();
    qDebug().noquote() <<  "[" << __func__<< "]" << "TO card balance" <<  _cardService->getCardById(thirdCard.id()).balance();
    qDebug().noquote() <<  "[" << __func__<< "]" << "Can Transfer" <<  condition4;


    bool condition1 = _cardService->getCardById(firstCard.id()).balance() == 100;
    bool condition2 = _cardService->getCardById(secondCard.id()).balance() == 400;
    bool condition3 = _cardService->getCardById(thirdCard.id()).balance() == 500;
    bool condition5 = _cardService->getCardById(fourthCard.id()).balance() == 0;

    return condition1 && condition2 && condition3 && !condition4 && condition5;

}

bool UnitTests::shouldMakeAutomaticTransaction()
{
    UserEntity firstUser = UserEntity(generateId(), "Slo Sloer");
    UserEntity secondUser = UserEntity(generateId(), "Rep Reper");
    _userRepository->setById(firstUser.id(), firstUser);
    _userRepository->setById(secondUser.id(), secondUser);

    CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),1000);
    _cardRepository->setById(firstCard.id(),firstCard );

    CardEntity secondCard(generateId(), generateCardId(), generatePin(),secondUser.id(),secondUser.name(),0);
    _cardRepository->setById(secondCard.id(),secondCard );


    _automaticTransactionService->createAutomaticTransaction(firstCard.cardId(), secondCard.cardId(),600,300,1,0);

    time_t startTime = time(0);
    time_t currentTime = time(0);
    long timeForOneTransaction = 1;

    qDebug().noquote() <<  "[" << __func__<< "]" << "START TIME: " << startTime;

    while (currentTime < startTime + timeForOneTransaction * 2) {
        _automaticTransactionService->checkAndExecute();
        currentTime = time(0);

        if(startTime + timeForOneTransaction > currentTime && startTime + 2 * timeForOneTransaction > currentTime){
//            qDebug().noquote() <<  "[" << __func__<< "]" << "ONE PART MUST BE TRANSFERED BY NOW";
            if(_cardService->getCardById(firstCard.id()).balance() != 700 ||
                    _cardService->getCardById(secondCard.id()).balance() != 300)
                return false;
        }
    }

    qDebug().noquote() <<  "[" << __func__<< "]" << "FINISH TIME: " << time(0);

    bool condition1 = _cardService->getCardById(firstCard.id()).balance() == 400;
    bool condition2 = _cardService->getCardById(secondCard.id()).balance() == 600;

    return condition1 && condition2;

}

bool UnitTests::shouldMakeAutomaticTransactionWithOddParts()
{
    UserEntity firstUser = UserEntity(generateId(), "Slo Sloer");
    UserEntity secondUser = UserEntity(generateId(), "Rep Reper");
    _userRepository->setById(firstUser.id(), firstUser);
    _userRepository->setById(secondUser.id(), secondUser);

    CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),1000);
    CardEntity secondCard(generateId(), generateCardId(), generatePin(),secondUser.id(),secondUser.name(),0);
    _cardRepository->setById(firstCard.id(),firstCard );
    _cardRepository->setById(secondCard.id(),secondCard );

    _automaticTransactionService->createAutomaticTransaction(firstCard.cardId(), secondCard.cardId(),500,200,1,0);
    qDebug().noquote() <<  "[" << __func__<< "]" << "START TIME: " << time(0);

    QThread::sleep(4); //bad, but it's only for testing
    _automaticTransactionService->checkAndExecute();

    qDebug().noquote() <<  "[" << __func__<< "]" << "FINISH TIME: " << time(0);

    bool condition1 = _cardService->getCardById(firstCard.id()).balance() == 500;
    bool condition2 = _cardService->getCardById(secondCard.id()).balance() == 500;

    vector<TransactionEntity> myTransactions =
            _transactionService->getSentTransactions(firstCard.id());

    qDebug().noquote() <<  "[" << __func__<< "]" << "Transaction count: " << myTransactions.size();

    bool condition3 = myTransactions.at(myTransactions.size() - 1).amount() == 100;
    bool condition4 = myTransactions.at(myTransactions.size() - 2).amount() == 200;
    bool condition5 = myTransactions.at(myTransactions.size() - 3).amount() == 200;

    return condition1 && condition2 && condition3 && condition4 && condition5;

}

bool UnitTests::shouldMakeAutomaticTransactionWithOddPartsAndReserveCards()
{
    UserEntity firstUser = UserEntity(generateId(), "Moo Mooer");
    UserEntity secondUser = UserEntity(generateId(), "Den Dener");
    _userRepository->setById(firstUser.id(), firstUser);
    _userRepository->setById(secondUser.id(), secondUser);

    CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),500);
    CardEntity secondCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),300);
    CardEntity thirdCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),200);
    CardEntity fourthCard(generateId(), generateCardId(), generatePin(),secondUser.id(),secondUser.name(),0);
    _cardRepository->setById(firstCard.id(),firstCard );
    _cardRepository->setById(secondCard.id(),secondCard );
    _cardRepository->setById(thirdCard.id(),thirdCard );
    _cardRepository->setById(fourthCard.id(),fourthCard );

    _cardService->setAsReserveCard(_cardService->getCardById(firstCard.id()).cardId(),
                                   _cardService->getCardById(secondCard.id()).cardId(), 0);

    _cardService->setAsReserveCard(_cardService->getCardById(secondCard.id()).cardId(),
                                   _cardService->getCardById(thirdCard.id()).cardId(), 0);

    _automaticTransactionService->createAutomaticTransaction(firstCard.cardId(), fourthCard.cardId(),1000,300,0,0);
    qDebug().noquote() <<  "[" << __func__<< "]" << "START TIME: " << time(0);

    QThread::sleep(1); //bad, but it's only for testing
    _automaticTransactionService->checkAndExecute();

    qDebug().noquote() <<  "[" << __func__<< "]" << "FINISH TIME: " << time(0);

    bool condition1 = _cardService->getCardById(firstCard.id()).balance() == 0;
    bool condition2 = _cardService->getCardById(secondCard.id()).balance() == 0;
    bool condition3 = _cardService->getCardById(thirdCard.id()).balance() == 0;
    bool condition4 = _cardService->getCardById(fourthCard.id()).balance() == 1000;

    vector<TransactionEntity> myTransactions =
            _transactionService->getSentTransactions(firstCard.id());

    qDebug().noquote() <<  "[" << __func__<< "]" << "Transaction count: " << myTransactions.size();

    bool condition5 = myTransactions.at(myTransactions.size() - 1).amount() == 100;
    bool condition6 = myTransactions.at(myTransactions.size() - 2).amount() == 300;
    bool condition7 = myTransactions.at(myTransactions.size() - 3).amount() == 300;

    return condition1 && condition2 && condition3 && condition4 && condition5 && condition6 && condition7;

}

bool UnitTests::shouldMakeFirstPartOfAutomaticTransaction()
{
    UserEntity firstUser = UserEntity(generateId(), "Err Errer");
    UserEntity secondUser = UserEntity(generateId(), "Seen Seener");
    _userRepository->setById(firstUser.id(), firstUser);
    _userRepository->setById(secondUser.id(), secondUser);

    CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),1000);
    _cardRepository->setById(firstCard.id(),firstCard );

    CardEntity secondCard(generateId(), generateCardId(), generatePin(),secondUser.id(),secondUser.name(),0);
    _cardRepository->setById(secondCard.id(),secondCard );


    _automaticTransactionService->createAutomaticTransaction(firstCard.cardId(), secondCard.cardId(),500,300,2,0);

    QThread::sleep(1);

    _automaticTransactionService->checkAndExecute();

    bool condition1 = _cardService->getCardById(firstCard.id()).balance() == 700;
    bool condition2 = _cardService->getCardById(secondCard.id()).balance() == 300;

    return condition1 && condition2;


}

bool UnitTests::shouldFailAutomaticTransaction()
{
    UserEntity firstUser = UserEntity(generateId(), "Err Errer");
    UserEntity secondUser = UserEntity(generateId(), "Seen Seener");
    _userRepository->setById(firstUser.id(), firstUser);
    _userRepository->setById(secondUser.id(), secondUser);

    CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),200);
    _cardRepository->setById(firstCard.id(),firstCard );

    CardEntity secondCard(generateId(), generateCardId(), generatePin(),secondUser.id(),secondUser.name(),0);
    _cardRepository->setById(secondCard.id(),secondCard );


    _automaticTransactionService->createAutomaticTransaction(firstCard._card_id, secondCard._card_id,500,100,0,0);

    QThread::sleep(1);

    _automaticTransactionService->checkAndExecute();

    bool condition1 = _cardService->getCardById(firstCard.id()).balance() == 0;
    bool condition2 = _cardService->getCardById(secondCard.id()).balance() == 200;
    bool condition3 = _automaticTransactionService->getAllAutomaticTransactionsFromMe(firstCard.id()).at(0).aborted() == true;

    return condition1 && condition2 && condition3;


}

bool UnitTests::throwsCircularDependencyException(){
    UserEntity firstUser = UserEntity(generateId(), "Nan Naner");
    _userRepository->setById(firstUser.id(), firstUser);

    CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),500);
    CardEntity secondCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),300);
    CardEntity thirdCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),200);
    _cardRepository->setById(firstCard.id(),firstCard );
    _cardRepository->setById(secondCard.id(),secondCard );
    _cardRepository->setById(thirdCard.id(),thirdCard );

    try {
        _cardService->setAsReserveCard(_cardService->getCardById(firstCard.id()).cardId(),
                                       _cardService->getCardById(secondCard.id()).cardId(), 0);

        _cardService->setAsReserveCard(_cardService->getCardById(secondCard.id()).cardId(),
                                       _cardService->getCardById(thirdCard.id()).cardId(), 0);
        _cardService->setAsReserveCard(_cardService->getCardById(secondCard.id()).cardId(),
                                       _cardService->getCardById(firstCard.id()).cardId(), 0);
    }  catch (CircularDependancyException) {
        return true;
    }

    return false;
}

bool UnitTests::throwsIncorrectCardAuthException(){
    UserEntity firstUser = UserEntity(generateId(), "Oom Oomer");
    _userRepository->setById(firstUser.id(), firstUser);

    CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),500);

    _cardRepository->setById(firstCard.id(),firstCard );


    try {
        _cardService->getCardIdByCredentials(firstCard.cardId(),-1);
    }  catch (IncorrectCardAuthInfoException) {
        return true;
    }

    return false;
}

bool UnitTests::throwsNotFoundException(){
    UserEntity firstUser = UserEntity(generateId(), "Yak Yaker");
    UserEntity secondUser = UserEntity(generateId(), "Sira Siraer");
    _userRepository->setById(firstUser.id(), firstUser);
    _userRepository->setById(secondUser.id(), secondUser);

    CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),1000);
    _cardRepository->setById(firstCard.id(),firstCard );

    CardEntity secondCard(generateId(), generateCardId(), generatePin(),secondUser.id(),secondUser.name(),0);
    _cardRepository->setById(secondCard.id(),secondCard );


    _transactionService->Transfer(100, firstCard.id(),secondCard.id());

    try {
        _transactionService->getSentTransactions(-1);
    }  catch (NotFoundException) {
        return true;
    }

    return false;

}

bool UnitTests::throwsLogicConflictException(){
    UserEntity firstUser = UserEntity(generateId(), "Nan Naner");
    _userRepository->setById(firstUser.id(), firstUser);

    CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),500);
    CardEntity secondCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),300);
    _cardRepository->setById(firstCard.id(),firstCard );
    _cardRepository->setById(secondCard.id(),secondCard );
    try {
        _cardService->setAsReserveCard(_cardService->getCardById(firstCard.id()).cardId(),
                                       _cardService->getCardById(secondCard.id()).cardId(), 700);

    }  catch (LogicConflictException) {
        return true;
    }

    return false;
}

bool UnitTests::throwsLogicConflictExceptionOverflow(){
    UserEntity firstUser = UserEntity(generateId(), "Nan Naner");
    _userRepository->setById(firstUser.id(), firstUser);

    CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),1000);
    CardEntity secondCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),300);
    _cardRepository->setById(firstCard.id(),firstCard );
    _cardRepository->setById(secondCard.id(),secondCard );
    try {
        _cardService->setAsOverflowCard(_cardService->getCardById(firstCard.id()).cardId(),
                                       _cardService->getCardById(secondCard.id()).cardId(), 700);

    }  catch (LogicConflictException) {
        return true;
    }

    return false;
}
