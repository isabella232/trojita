#include <QAuthenticator>
#include "MailboxTree.h"
#include "SelectingHandler.h"

namespace Imap {
namespace Mailbox {

SelectingHandler::SelectingHandler( Model* _m ): ModelStateHandler(_m)
{
}


void SelectingHandler::handleState( Imap::ParserPtr ptr, const Imap::Responses::State* const resp )
{
    m->authenticatedHandler->handleState( ptr, resp );
}

void SelectingHandler::handleNumberResponse( Imap::ParserPtr ptr, const Imap::Responses::NumberResponse* const resp )
{
    // FIXME ?
    throw UnexpectedResponseReceived( "Numeric reply while syncing mailbox", *resp );
}

void SelectingHandler::handleList( Imap::ParserPtr ptr, const Imap::Responses::List* const resp )
{
    m->authenticatedHandler->handleList( ptr, resp );
}

void SelectingHandler::handleFlags( Imap::ParserPtr ptr, const Imap::Responses::Flags* const resp )
{
    throw UnexpectedResponseReceived( "FLAGS reply while syncing mailbox", *resp );
}

void SelectingHandler::handleSearch( Imap::ParserPtr ptr, const Imap::Responses::Search* const resp )
{
    throw UnexpectedResponseReceived( "SEARCH reply while syncing mailbox", *resp );
}

void SelectingHandler::handleFetch( Imap::ParserPtr ptr, const Imap::Responses::Fetch* const resp )
{
    TreeItemMailbox* mailbox = m->_parsers[ ptr.get() ].currentMbox;
    if ( ! mailbox )
        throw UnexpectedResponseReceived( "Received FETCH reply, but we don't know what mailbox are we syncing", *resp );

    mailbox->handleFetchWhileSyncing( m, ptr, *resp );
}

}
}

#include "SelectingHandler.moc"
