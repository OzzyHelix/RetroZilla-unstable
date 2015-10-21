/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef TOOLKIT_H      
#define TOOLKIT_H

#include "nsToolkitBase.h"

/**
 * The toolkit abstraction is necessary because the message pump must
 * execute within the same thread that created the widget under Win32.
 * We don't care about that on Mac: we have only one thread for the UI
 * and maybe even for the whole application.
 * 
 * So on the Mac, the nsToolkit used to be a unique object, created once
 * at startup along with nsAppShell and passed to all the top-level
 * windows and it became a convenient place to throw in everything we
 * didn't know where else to put, like the NSPR event queue and
 * the handling of global pointers on some special widgets (focused
 * widget, widget hit, widget pointed).
 *
 * All this has changed: the application now usually creates one copy of
 * the nsToolkit per window and the special widgets had to be moved
 * to the nsMacEventHandler.
 */

#include <MacTypes.h>
#include <MacWindows.h>

class nsIEventSink;
class nsIWidget;
class nsIView;
class nsIDocument;

#define MAC_OS_X_VERSION_10_0_HEX 0x00001000
#define MAC_OS_X_VERSION_10_1_HEX 0x00001010
#define MAC_OS_X_VERSION_10_2_HEX 0x00001020
#define MAC_OS_X_VERSION_10_3_HEX 0x00001030
#define MAC_OS_X_VERSION_10_4_HEX 0x00001040

class nsToolkit : public nsToolkitBase
{

public:
  nsToolkit();
  virtual				~nsToolkit();
  
protected:

  virtual nsresult  InitEventQueue(PRThread * aThread);

public:

  // utility routines for getting the toplevel widget and event sink
  // stashed in properties of the window.
  static void GetWindowEventSink ( WindowPtr aWindow, nsIEventSink** outSink ) ;
  static void GetTopWidget ( WindowPtr aWindow, nsIWidget** outWidget ) ;
  // Utility routines for wringing nsIDocument or nsIView info from an nsIWidget
  static nsIView *GetViewFor(nsIWidget *aWidget);
  static nsIDocument *GetDocumentFor(nsIWidget *aWidget);

  // Returns the OS X version as returned from
  // Gestalt(gestaltSystemVersion, ...)
  static long OSXVersion ( ) ;
};
#endif  // TOOLKIT_H
