#include "automatictransactionservice.h"

AutomaticTransactionService* AutomaticTransactionService::_service = nullptr;

AutomaticTransactionService::AutomaticTransactionService() : _transaction_rep(TransactionRepositoryVectorImpl::getInstance()),
    _a_tr_rep(AutomaticTransactionRepositoryVectorImpl::getInstance())
{

}
