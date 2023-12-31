/*
 * Copyright (c) 2023, Red Hat, Inc. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
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

/*
 * @test
 * bug 8313262
 * @summary Sinking node may cause required cast to be dropped
 * @requires vm.gc.Shenandoah
 * @run main/othervm -XX:-BackgroundCompilation -XX:+UseShenandoahGC TestSinkingNodeDropsNotNullCast
 */

import java.util.Arrays;

public class TestSinkingNodeDropsNotNullCast {
    public static void main(String[] args) {
        Object[] array1 = new Object[100];
        Object[] array2 = new Object[100];
        Arrays.fill(array2, new Object());
        for (int i = 0; i < 20_000; i++) {
            test(array1);
            test(array1);
            test(array2);
        }
    }

    private static Object test(Object[] array) {
        Object o;
        int i = 1;
        do {
            synchronized (new Object()) {
            }
            o = array[i];
            if (o != null) {
                if (o instanceof A) {
                    return ((A) o).field;
                } else {
                    return o;
                }
            }
            i++;
        } while (i < 100);
        return o;
    }

    private static class A {
        Object field;
    }
}
