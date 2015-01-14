#ifndef __HERDERGATEWAY__
#define __HERDERGATEWAY__

// Copyright 2014 Stellar Development Foundation and contributors. Licensed
// under the ISC License. See the COPYING file at the top-level directory of
// this distribution or at http://opensource.org/licenses/ISC

#include <memory>
#include "generated/StellarXDR.h"
#include "generated/FBAXDR.h"

namespace stellar
{
class TxSetFrame;
typedef std::shared_ptr<TxSetFrame> TxSetFramePtr;

class TransactionFrame;
typedef std::shared_ptr<TransactionFrame> TransactionFramePtr;

class Peer;
typedef std::shared_ptr<Peer> PeerPtr;

/*
 * Public Interface to the Herder module
 *
 * Drives the FBA consensus protocol, is responsible for collecting Txs and
 * TxSets from the network and making sure Txs aren't lost in ledger close
 *
 * LATER: These gateway interface need cleaning up. We need to work out how to
 * make the bidirectional interfaces
 */
class HerderGateway
{
  public:
    // Returns a TxSet or start fetching it from the network if we don't know
    // about it.
    virtual TxSetFramePtr fetchTxSet(uint256 const& setHash,
                                     bool askNetwork) = 0;

    // Called by Overlay when A Tx set comes in from the wire
    virtual void recvTransactionSet(TxSetFramePtr txSet) = 0;
    virtual void doesntHaveTxSet(uint256 const& setHash,
                                 PeerPtr peer) = 0;

    // We are learning about a new transaction. Returns true if we should flood
    // this tx.
    virtual bool recvTransaction(TransactionFramePtr tx) = 0;

    // Called by Ledger once the ledger closes.
    virtual void ledgerClosed(LedgerHeader& ledger) = 0;
};
}

#endif
