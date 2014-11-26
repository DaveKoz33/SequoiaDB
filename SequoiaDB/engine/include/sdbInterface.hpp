/*******************************************************************************


   Copyright (C) 2011-2014 SequoiaDB Ltd.

   This program is free software: you can redistribute it and/or modify
   it under the term of the GNU Affero General Public License, version 3,
   as published by the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warrenty of
   MARCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program. If not, see <http://www.gnu.org/license/>.

   Source File Name = sdbInterface.hpp

   Descriptive Name = Process MoDel Engine Dispatchable Unit Event Header

   When/how to use: this program may be used on binary and text-formatted
   versions of PMD component. This file contains structure for events that
   used as inter-EDU communications.

   Dependencies: N/A

   Restrictions: N/A

   Change Activity:
   defect Date        Who Description
   ====== =========== === ==============================================
          09/14/2012  TW  Initial Draft

   Last Changed =

*******************************************************************************/
#ifndef SDB_INTERFACE_HPP__
#define SDB_INTERFACE_HPP__

#include "core.hpp"
#include "oss.hpp"
#include "msg.h"

namespace engine
{

   /*
      ENUM define
   */
   enum SDB_CB_TYPE
   {
      SDB_CB_DPS              = 0,
      SDB_CB_DMS,
      SDB_CB_BPS,
      SDB_CB_RTN,
      SDB_CB_TRANS,           // must after SDB_CB_DPS
      SDB_CB_CATALOGUE,
      SDB_CB_CLS,             // must after SDB_CB_CATALOGUE
      SDB_CB_COORD,
      SDB_CB_SQL,
      SDB_CB_AUTH,
      SDB_CB_AGGR,
      SDB_CB_FMP,
      SDB_CB_OMSVC,
      SDB_CB_OMAGT,

      SDB_CB_PMDCTRL,
      SDB_CB_MAX
   } ;

   /*
      SDB_INTERFACE_TYPE DEFINE
   */
   enum SDB_INTERFACE_TYPE
   {
      SDB_IF_CB      = 1,
      SDB_IF_SESSION,
      SDB_IF_EVT_HANDLER,
      SDB_IF_EVT_HOLDER,

      SDB_IF_MAX
   } ;

   /*
      SDB_SESSION_TYPE define
   */
   enum SDB_SESSION_TYPE
   {
      SDB_SESSION_LOCAL       = 0,
      SDB_SESSION_REST,
      SDB_SESSION_REPL,
      SDB_SESSION_SHARD,
      SDB_SESSION_FS_SRC,
      SDB_SESSION_FS_DST,
      SDB_SESSION_SPLIT_SRC,
      SDB_SESSION_SPLIT_DST,
      SDB_SESSION_OMAGENT,

      SDB_SESSION_MAX
   } ;

   class _ISDBRoot
   {
      public:
         _ISDBRoot () {}
         virtual ~_ISDBRoot () {}

         virtual void* queryInterface( SDB_INTERFACE_TYPE type )
         {
            return NULL ;
         }
   } ;
   typedef _ISDBRoot ISDBRoot ;

   /*
      EVENT MASK DEFINE
   */
   #define EVENT_MASK_ON_REGISTERED          0x00000001
   #define EVENT_MASK_ON_PRIMARYCHG          0x00000002

   enum SDB_EVENT_OCCUR_TYPE
   {
      SDB_EVT_OCCUR_BEFORE   = 1,
      SDB_EVT_OCCUR_AFTER
   } ;

   /*
      _IEventHander define
   */
   class _IEventHander
   {
      public :
         _IEventHander () {}
         virtual ~_IEventHander () {}

         virtual UINT32 getMask() const = 0 ;

         virtual void   onRegistered( const MsgRouteID &nodeID )
         {}
         virtual void   onPrimaryChange( BOOLEAN primary,
                                         SDB_EVENT_OCCUR_TYPE occurType )
         {}

   } ;
   typedef _IEventHander IEventHander ;

   /*
      _IEventHolder define
   */
   class _IEventHolder
   {
      public:
         _IEventHolder () {}
         virtual ~_IEventHolder () {}

         virtual INT32  regEventHandler( IEventHander *pHandler ) = 0 ;
         virtual void   unregEventHandler( IEventHander *pHandler ) = 0 ;
   } ;
   typedef _IEventHolder IEventHolder ;

   /*
      _IConfigHandle define
   */
   class _IConfigHandle
   {
      public:
         _IConfigHandle () {}
         virtual ~_IConfigHandle () {}

         virtual void   onConfigChange ( UINT32 changeID ) = 0 ;
         virtual INT32  onConfigInit () = 0 ;
   } ;
   typedef _IConfigHandle IConfigHandle ;

   /*
      _pmdBaseSession define
   */
   class _ISession : public SDBObject
   {
      public:
         _ISession() {}
         virtual ~_ISession() {}

      public:
         virtual UINT64             identifyID() = 0 ;
         virtual const CHAR*        sessionName() const = 0 ;
         virtual SDB_SESSION_TYPE   sessionType() const = 0 ;
         virtual INT32              getServiceType() const = 0 ;

      protected:
         virtual void               _onAttach () {}
         virtual void               _onDetach () {}

   } ;
   typedef _ISession ISession ;

   /*
      _IControlBlock define
   */
   class _IControlBlock : public SDBObject, public _ISDBRoot
   {
      public:
         _IControlBlock () {}
         virtual ~_IControlBlock () {}

         virtual SDB_CB_TYPE cbType() const = 0 ;
         virtual const CHAR* cbName() const = 0 ;

         virtual INT32  init () = 0 ;
         virtual INT32  active () = 0 ;
         virtual INT32  deactive () = 0 ;
         virtual INT32  fini () = 0 ;
         virtual void   onConfigChange() {}

   } ;
   typedef _IControlBlock IControlBlock ;

}

#endif // SDB_INTERFACE_HPP__
