/*
 * Copyright (c) 1998, 2013, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */
#ifndef _AWT_MLIB_H_
#define _AWT_MLIB_H_

#include "awt_ImagingLib.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef void (*mlib_start_timer)(int);
typedef void (*mlib_stop_timer)(int, int);

mlib_status awt_getImagingLib(JNIEnv *env, mlibFnS_t *sMlibFns,
                                        mlibSysFnS_t *sMlibSysFns);
mlib_start_timer awt_setMlibStartTimer();
mlib_stop_timer awt_setMlibStopTimer();

#ifdef __cplusplus
} /* end of extern "C" */
#endif



#endif /* _AWT_MLIB_H */
