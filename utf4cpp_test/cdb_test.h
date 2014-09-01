/* This file is part of utf4cpp.
 * Copyright (C) 2014 Marcos Cambon */


/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#ifndef CDB_TEST_H
#define CDB_TEST_H

namespace test {
	

class cdb_test {

public:
	cdb_test();
	~cdb_test();
	static void cdb_values_test();
	static void performance_test();


	static boost::unit_test::test_suite* test_suite();

};

}
#endif // CDB_TEST_H
