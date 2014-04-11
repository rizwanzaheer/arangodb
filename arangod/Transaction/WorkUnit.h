////////////////////////////////////////////////////////////////////////////////
/// @brief transaction unit of work
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2004-2013 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Jan Steemann
/// @author Copyright 2011-2013, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_TRANSACTION_WORK_UNIT_H
#define TRIAGENS_TRANSACTION_WORK_UNIT_H 1

#include "Basics/Common.h"
#include "Basics/BsonHelper.h"
#include "Transaction/Collection.h"
#include "Transaction/State.h"
#include "Transaction/Transaction.h"

namespace triagens {
  namespace transaction {

    class Context;

// -----------------------------------------------------------------------------
// --SECTION--                                                    class WorkUnit
// -----------------------------------------------------------------------------

    class WorkUnit : public State {

////////////////////////////////////////////////////////////////////////////////
/// @brief Context
////////////////////////////////////////////////////////////////////////////////

      private:
        WorkUnit (WorkUnit const&);
        WorkUnit& operator= (WorkUnit const&);

// -----------------------------------------------------------------------------
// --SECTION--                                      constructors and destructors
// -----------------------------------------------------------------------------

      public:

////////////////////////////////////////////////////////////////////////////////
/// @brief create a transaction work unit
////////////////////////////////////////////////////////////////////////////////

        WorkUnit (Context*,
                  bool); 

////////////////////////////////////////////////////////////////////////////////
/// @brief destroy a transaction work unit
////////////////////////////////////////////////////////////////////////////////

        ~WorkUnit ();

// -----------------------------------------------------------------------------
// --SECTION--                                                    public methods
// -----------------------------------------------------------------------------

      public:

////////////////////////////////////////////////////////////////////////////////
/// @brief id of the work unit
////////////////////////////////////////////////////////////////////////////////

        inline uint64_t id () const {
          return _id;
        }

////////////////////////////////////////////////////////////////////////////////
/// @brief whether or not the unit contains just a single operation
////////////////////////////////////////////////////////////////////////////////

        inline bool isSingleOperation () const {
          return _singleOperation;
        }

////////////////////////////////////////////////////////////////////////////////
/// @brief add a collection to the unit, assert a specific collection type
////////////////////////////////////////////////////////////////////////////////

        Collection* addCollection (std::string const&,
                                   Collection::AccessType,
                                   TRI_col_type_e,
                                   bool = true,
                                   bool = false);

////////////////////////////////////////////////////////////////////////////////
/// @brief add a collection to the unit
////////////////////////////////////////////////////////////////////////////////

        Collection* addCollection (std::string const&,
                                   Collection::AccessType,
                                   bool = true,
                                   bool = false);

////////////////////////////////////////////////////////////////////////////////
/// @brief add a collection to the unit
////////////////////////////////////////////////////////////////////////////////
        
        Collection* addCollection (TRI_voc_cid_t,
                                   TRI_vocbase_col_t*,
                                   Collection::AccessType,
                                   bool = true,
                                   bool = false);

////////////////////////////////////////////////////////////////////////////////
/// @brief find a collection in a unit of work
////////////////////////////////////////////////////////////////////////////////

        Collection* findCollection (TRI_voc_cid_t) const;

////////////////////////////////////////////////////////////////////////////////
/// @brief begin a unit of work
////////////////////////////////////////////////////////////////////////////////

        int begin ();

////////////////////////////////////////////////////////////////////////////////
/// @brief commit a unit of work
////////////////////////////////////////////////////////////////////////////////

        int commit (bool = false);

////////////////////////////////////////////////////////////////////////////////
/// @brief rollback a unit of work
////////////////////////////////////////////////////////////////////////////////

        int rollback ();

////////////////////////////////////////////////////////////////////////////////
/// @brief save a single document
////////////////////////////////////////////////////////////////////////////////

        int saveDocument (Collection*,
                          triagens::basics::Bson&,
                          bool);

// -----------------------------------------------------------------------------
// --SECTION--                                                   private methods
// -----------------------------------------------------------------------------

      private:

////////////////////////////////////////////////////////////////////////////////
/// @brief whether or not we are on the top level
////////////////////////////////////////////////////////////////////////////////

// TODO: remove
        inline bool isTopLevel () const {
          return _level == 0;
        }

////////////////////////////////////////////////////////////////////////////////
/// @brief set the unit of work to done
////////////////////////////////////////////////////////////////////////////////

        void done ();

////////////////////////////////////////////////////////////////////////////////
/// @brief cleanup the unit of work
////////////////////////////////////////////////////////////////////////////////

        void cleanup ();

// -----------------------------------------------------------------------------
// --SECTION--                                                 private variables
// -----------------------------------------------------------------------------

      private:

////////////////////////////////////////////////////////////////////////////////
/// @brief the transaction context
////////////////////////////////////////////////////////////////////////////////

        Context* _context;

////////////////////////////////////////////////////////////////////////////////
/// @brief the participating collections
////////////////////////////////////////////////////////////////////////////////

        std::map<TRI_voc_cid_t, Collection*> _collections;

////////////////////////////////////////////////////////////////////////////////
/// @brief the work unit id inside the current context
////////////////////////////////////////////////////////////////////////////////

        uint64_t const _id;

////////////////////////////////////////////////////////////////////////////////
/// @brief the current level we are in
////////////////////////////////////////////////////////////////////////////////

        int const _level;

////////////////////////////////////////////////////////////////////////////////
/// @brief whether or not the unit will contain just a single operation
////////////////////////////////////////////////////////////////////////////////

        bool const _singleOperation;

////////////////////////////////////////////////////////////////////////////////
/// @brief whether or not the work unit was done
////////////////////////////////////////////////////////////////////////////////

        bool _done;

    };

  }
}

#endif

// Local Variables:
// mode: outline-minor
// outline-regexp: "/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|/// @page\\|// --SECTION--\\|/// @\\}"
// End:
