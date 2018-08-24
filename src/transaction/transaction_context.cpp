
#include "common/exception.hpp"

#include "transaction/transaction_context.hpp"

using namespace duckdb;
using namespace std;

TransactionContext::~TransactionContext() {}

void TransactionContext::BeginTransaction() {
	if (current_transaction) {
		throw Exception("Transaction is already running!");
	}
	current_transaction = transaction_manager.StartTransaction();
}

void TransactionContext::Commit() {
	if (!current_transaction) {
		throw Exception("No transaction is currently active - cannot commit!");
	}
	transaction_manager.CommitTransaction(current_transaction);
	current_transaction = nullptr;
}

void TransactionContext::Rollback() {
	if (!current_transaction) {
		throw Exception(
		    "No transaction is currently active - cannot rollback!");
	}
	transaction_manager.RollbackTransaction(current_transaction);
	current_transaction = nullptr;
}
