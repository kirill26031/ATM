#include "unittests.h"



UnitTests::UnitTests()
{
    userRepository = UserRepositoryVectorImpl::getInstance();
    cardRepository = CardRepositoryVectorImpl::getInstance();
    transactionRepository = TransactionRepositoryVectorImpl::getInstance();
    cardService  = CardService::getInstance();
    transactionService  = TransactionService::getInstance();

}

void UnitTests::runTests()
{
    qDebug() << "======RUNNING TESTS=======";

    _testResults.push_back(qMakePair("shouldSuccessfullyCreateNewUser", shouldSuccessfullyCreateNewUser()));
    _testResults.push_back(qMakePair("shouldCreateLinkCardsToUser", shouldCreateLinkCardsToUser()));
    _testResults.push_back(qMakePair("shouldMakeTransactionsWithoutReserveCard", shouldMakeTransactionsWithoutReserveCard()));
    _testResults.push_back(qMakePair("shouldMakeTransactionsWithReserveCard", shouldMakeTransactionsWithReserveCard()));
    _testResults.push_back(qMakePair("shouldMakeTransactionsWithMultipleReserveCards", shouldMakeTransactionsWithMultipleReserveCards()));

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

}

bool UnitTests::shouldSuccessfullyCreateNewUser()
{
     UserEntity firstUser = UserEntity(generateId(), "Bob Bobber");
     UserEntity secondUser = UserEntity(generateId(), "Sam Sammer");
     userRepository->setById(firstUser.id(), firstUser);
     userRepository->setById(secondUser.id(), secondUser);
     if(userRepository->existsById(firstUser.id()) && userRepository->existsById(secondUser.id())){
         string names = userRepository->getById(firstUser.id()).name() + ", "
                 + userRepository->getById(secondUser.id()).name();
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
    userRepository->setById(firstUser.id(), firstUser);
    userRepository->setById(secondUser.id(), secondUser);

    long firstCard = cardService->generateCard(firstUser.id(), firstUser.name());
    long secondCard = cardService->generateCard(secondUser.id(), secondUser.name());
    long thirdCard = cardService->generateCard(secondUser.id(), secondUser.name());
    cardService->setAsReserveCard(cardService->getCardById(secondCard).cardId(),
                                  cardService->getCardById(thirdCard).cardId(), 0);
    qDebug().noquote() <<  "[" << __func__<< "]" << cardService->getCardById(firstCard).pin();
    qDebug().noquote() <<  "[" << __func__<< "]" << cardService->getCardById(secondCard).pin();
    qDebug().noquote() <<  "[" << __func__<< "]" << cardService->getCardById(thirdCard).pin();

    bool condition1 = cardService->getCardById(firstCard).id() == firstCard;
    bool condition2 = cardService->getCardById(secondCard).id() == secondCard;
    bool condition3 = cardService->getCardById(secondCard).balance() == 0;
    bool condition4 = *(cardService->getCardById(secondCard).reserveCardId()) == thirdCard;

    return condition1 && condition2 && condition3 && condition4;


}

bool UnitTests::shouldMakeTransactionsWithoutReserveCard()
{
    UserEntity firstUser = UserEntity(generateId(), "Test Tester");
    UserEntity secondUser = UserEntity(generateId(), "Cooc Coocer");
    userRepository->setById(firstUser.id(), firstUser);
    userRepository->setById(secondUser.id(), secondUser);

   CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),1000);
   cardRepository->setById(firstCard.id(),firstCard );

   CardEntity secondCard(generateId(), generateCardId(), generatePin(),secondUser.id(),secondUser.name(),0);
   cardRepository->setById(secondCard.id(),secondCard );


   transactionService->Transfer(500, firstCard.id(),secondCard.id());

   bool condition1 = cardService->getCardById(firstCard.id()).balance() == 500;
   bool condition2 = cardService->getCardById(secondCard.id()).balance() == 500;

   return condition1 && condition2;

}

bool UnitTests::shouldMakeTransactionsWithReserveCard()
{
    UserEntity firstUser = UserEntity(generateId(), "New Newer");
    UserEntity secondUser = UserEntity(generateId(), "Old Older");
    userRepository->setById(firstUser.id(), firstUser);
    userRepository->setById(secondUser.id(), secondUser);

   CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),300);
   CardEntity secondCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),500);
   cardRepository->setById(firstCard.id(),firstCard );
   cardRepository->setById(secondCard.id(),secondCard );
   cardService->setAsReserveCard(cardService->getCardById(firstCard.id()).cardId(),
                                 cardService->getCardById(secondCard.id()).cardId(), 0);

   CardEntity thirdCard(generateId(), generateCardId(), generatePin(),secondUser.id(),secondUser.name(),0);
   cardRepository->setById(thirdCard.id(),thirdCard );


   bool condition4 = transactionService->Transfer(500, firstCard.id(), thirdCard.id());

   qDebug().noquote() <<  "[" << __func__<< "]" << "FROM card balance" << cardService->getCardById(firstCard.id()).balance();
   qDebug().noquote() <<  "[" << __func__<< "]" << "RESERVE card balance" <<  cardService->getCardById(secondCard.id()).balance();
   qDebug().noquote() <<  "[" << __func__<< "]" << "TO card balance" <<  cardService->getCardById(thirdCard.id()).balance();
   qDebug().noquote() <<  "[" << __func__<< "]" << "Can Transfer" <<  condition4;


   bool condition1 = cardService->getCardById(firstCard.id()).balance() == 0;
   bool condition2 = cardService->getCardById(secondCard.id()).balance() == 300;
   bool condition3 = cardService->getCardById(thirdCard.id()).balance() == 500;

   return condition1 && condition2 && condition3 && condition4;

}

bool UnitTests::shouldMakeTransactionsWithMultipleReserveCards()
{
    UserEntity firstUser = UserEntity(generateId(), "Will Willer");
    UserEntity secondUser = UserEntity(generateId(), "Sonya Sonyer");
    userRepository->setById(firstUser.id(), firstUser);
    userRepository->setById(secondUser.id(), secondUser);

   CardEntity firstCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),500);
   CardEntity secondCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),300);
   CardEntity thirdCard(generateId(), generateCardId(), generatePin(),firstUser.id(),firstUser.name(),200);
   CardEntity fourthCard(generateId(), generateCardId(), generatePin(),secondUser.id(),secondUser.name(),0);
   cardRepository->setById(firstCard.id(),firstCard );
   cardRepository->setById(secondCard.id(),secondCard );
   cardRepository->setById(thirdCard.id(),thirdCard );
   cardRepository->setById(fourthCard.id(),fourthCard );

   cardService->setAsReserveCard(cardService->getCardById(firstCard.id()).cardId(),
                                 cardService->getCardById(secondCard.id()).cardId(), 0);

   cardService->setAsReserveCard(cardService->getCardById(secondCard.id()).cardId(),
                                 cardService->getCardById(thirdCard.id()).cardId(), 0);


   bool condition4 = transactionService->Transfer(900, firstCard.id(), fourthCard.id());

   qDebug().noquote() <<  "[" << __func__<< "]" << "FROM card balance" << cardService->getCardById(firstCard.id()).balance();
   qDebug().noquote() <<  "[" << __func__<< "]" << "RESERVE card balance" <<  cardService->getCardById(secondCard.id()).balance();
   qDebug().noquote() <<  "[" << __func__<< "]" << "TO card balance" <<  cardService->getCardById(thirdCard.id()).balance();
   qDebug().noquote() <<  "[" << __func__<< "]" << "Can Transfer" <<  condition4;


   bool condition1 = cardService->getCardById(firstCard.id()).balance() == 0;
   bool condition2 = cardService->getCardById(secondCard.id()).balance() == 0;
   bool condition3 = cardService->getCardById(thirdCard.id()).balance() == 100;
   bool condition5 = cardService->getCardById(fourthCard.id()).balance() == 900;

   return condition1 && condition2 && condition3 && condition4 && condition5;

}



