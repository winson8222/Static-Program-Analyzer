#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include <iostream>
#include <chrono>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

#ifdef SKIP_STRESS_TESTS
// Mark the entire test case as skipped
TEST_CASE("sp/SourceProcessor: Stress tests") {
    SECTION("Stress") {

        auto start = std::chrono::high_resolution_clock::now();

        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = 
            "procedure deeplyNestedLogic {"
            "x = 100;"
            "if (x > 1) then {"
            "read y;} else {"
            "print x;while (x > 2) {"
            "x = x - 12;if (x > 3) then {"
            "print x;} else {"
            "read y;while (x > 4) {"
            "x = x - 14;if (x > 5) then {"
            "print x;} else {"
            "read x;while (x > 6) {"
            "x = x - 16;if (x > 7) then {"
            "print y;} else {"
            "print x;while (x > 8) {"
            "x = x - 18;if (x > 9) then {"
            "print y;} else {"
            "read y;while (x > 10) {"
            "x = x - 20;if (x > 11) then {"
            "print y;} else {"
            "print y;while (x > 12) {"
            "x = x - 22;if (x > 13) then {"
            "read y;} else {"
            "print y;while (x > 14) {"
            "x = x - 24;if (x > 15) then {"
            "read y;} else {"
            "read x;while (x > 16) {"
            "x = x - 26;if (x > 17) then {"
            "print y;} else {"
            "read x;while (x > 18) {"
            "x = x - 28;if (x > 19) then {"
            "read x;} else {"
            "print x;while (x > 20) {"
            "x = x - 30;if (x > 21) then {"
            "read x;} else {"
            "read x;while (x > 22) {"
            "x = x - 32;if (x > 23) then {"
            "print x;} else {"
            "read y;while (x > 24) {"
            "x = x - 34;if (x > 25) then {"
            "print y;} else {"
            "read x;while (x > 26) {"
            "x = x - 36;if (x > 27) then {"
            "print x;} else {"
            "print x;while (x > 28) {"
            "x = x - 38;if (x > 29) then {"
            "read x;} else {"
            "print y;while (x > 30) {"
            "x = x - 40;if (x > 31) then {"
            "print y;} else {"
            "print x;while (x > 32) {"
            "x = x - 42;if (x > 33) then {"
            "print x;} else {"
            "print y;while (x > 34) {"
            "x = x - 44;if (x > 35) then {"
            "print x;} else {"
            "read y;while (x > 36) {"
            "x = x - 46;if (x > 37) then {"
            "read x;} else {"
            "read y;while (x > 38) {"
            "x = x - 48;if (x > 39) then {"
            "print y;} else {"
            "print y;while (x > 40) {"
            "x = x - 50;if (x > 41) then {"
            "read x;} else {"
            "print x;while (x > 42) {"
            "x = x - 52;if (x > 43) then {"
            "read x;} else {"
            "print y;while (x > 44) {"
            "x = x - 54;if (x > 45) then {"
            "read x;} else {"
            "read x;while (x > 46) {"
            "x = x - 56;if (x > 47) then {"
            "print y;} else {"
            "read y;while (x > 48) {"
            "x = x - 58;if (x > 49) then {"
            "print x;} else {"
            "print y;while (x > 50) {"
            "x = x - 60;if (x > 51) then {"
            "print y;} else {"
            "print x;while (x > 52) {"
            "x = x - 62;if (x > 53) then {"
            "print y;} else {"
            "read x;while (x > 54) {"
            "x = x - 64;if (x > 55) then {"
            "print y;} else {"
            "read x;while (x > 56) {"
            "x = x - 66;if (x > 57) then {"
            "print x;} else {"
            "read x;while (x > 58) {"
            "x = x - 68;if (x > 59) then {"
            "print x;} else {"
            "print x;while (x > 60) {"
            "x = x - 70;if (x > 61) then {"
            "print x;} else {"
            "print y;while (x > 62) {"
            "x = x - 72;if (x > 63) then {"
            "print y;} else {"
            "read y;while (x > 64) {"
            "x = x - 74;if (x > 65) then {"
            "read y;} else {"
            "read x;while (x > 66) {"
            "x = x - 76;if (x > 67) then {"
            "read x;} else {"
            "read x;while (x > 68) {"
            "x = x - 78;if (x > 69) then {"
            "read x;} else {"
            "read y;while (x > 70) {"
            "x = x - 80;if (x > 71) then {"
            "print y;} else {"
            "read x;while (x > 72) {"
            "x = x - 82;if (x > 73) then {"
            "print y;} else {"
            "read y;while (x > 74) {"
            "x = x - 84;if (x > 75) then {"
            "read y;} else {"
            "print y;while (x > 76) {"
            "x = x - 86;if (x > 77) then {"
            "read x;} else {"
            "read x;while (x > 78) {"
            "x = x - 88;if (x > 79) then {"
            "read y;} else {"
            "print x;while (x > 80) {"
            "x = x - 90;if (x > 81) then {"
            "print y;} else {"
            "print x;while (x > 82) {"
            "x = x - 92;if (x > 83) then {"
            "read x;} else {"
            "read y;while (x > 84) {"
                "x = x - 94;if (x > 85) then {"
                "print y;} else {"
                "print y;while (x > 86) {"
                "x = x - 96;if (x > 87) then {"
                "read y;} else {"
                "read y;while (x > 88) {"
                "x = x - 98;if (x > 89) then {"
                "print x;} else {"
                "print x;while (x > 90) {"
                "x = x - 100;if (x > 91) then {"
                "print y;} else {"
                "print y;while (x > 92) {"
                "x = x - 102;if (x > 93) then {"
                "read y;} else {"
                "read x;while (x > 94) {"
                "x = x - 104;if (x > 95) then {"
                "read y;} else {"
                "read y;while (x > 96) {"
                "x = x - 106;if (x > 97) then {"
                "read x;} else {"
                "print x;while (x > 98) {"
                "x = x - 108;if (x > 99) then {"
                "read x;} else {"
                "read y;while (x > 100) {"
                "x = x - 110;if (x > 101) then {"
                "read x;} else {"
                "read y;while (x > 102) {"
                "x = x - 112;if (x > 103) then {"
                "read y;} else {"
                "print x;while (x > 104) {"
                "x = x - 114;if (x > 105) then {"
                "read x;} else {"
                "print y;while (x > 106) {"
                "x = x - 116;if (x > 107) then {"
                "print y;} else {"
                "read x;while (x > 108) {"
                "x = x - 118;if (x > 109) then {"
                "print y;} else {"
                "read x;while (x > 110) {"
                "x = x - 120;if (x > 111) then {"
                "read y;} else {"
                "read y;while (x > 112) {"
                "x = x - 122;if (x > 113) then {"
                "print y;} else {"
                "read y;while (x > 114) {"
                "x = x - 124;if (x > 115) then {"
                "read y;} else {"
                "print y;while (x > 116) {"
                "x = x - 126;if (x > 117) then {"
                "print x;} else {"
                "print y;while (x > 118) {"
                "x = x - 128;if (x > 119) then {"
                "print x;} else {"
                "read x;while (x > 120) {"
                "x = x - 130;if (x > 121) then {"
                "print x;} else {"
                "print x;while (x > 122) {"
                "x = x - 132;if (x > 123) then {"
                "read x;} else {"
                "read x;while (x > 124) {"
                "x = x - 134;if (x > 125) then {"
                "print y;} else {"
                "print y;while (x > 126) {"
                "x = x - 136;if (x > 127) then {"
                "print y;} else {"
                "print y;while (x > 128) {"
                "x = x - 138;if (x > 129) then {"
                "read x;} else {"
                "print y;while (x > 130) {"
                "x = x - 140;if (x > 131) then {"
                "read y;} else {"
                "read y;while (x > 132) {"
                "x = x - 142;if (x > 133) then {"
                "read x;} else {"
                "print x;while (x > 134) {"
                "x = x - 144;if (x > 135) then {"
                "read y;} else {"
                "print y;while (x > 136) {"
                "x = x - 146;if (x > 137) then {"
                "print y;} else {"
                "read x;while (x > 138) {"
                "x = x - 148;if (x > 139) then {"
                "read x;} else {"
                "print x;while (x > 140) {"
                "x = x - 150;if (x > 141) then {"
                "read x;} else {"
                "print y;while (x > 142) {"
                "x = x - 152;if (x > 143) then {"
                "print y;} else {"
                "print x;while (x > 144) {"
                "x = x - 154;if (x > 145) then {"
                "print y;} else {"
                "print x;while (x > 146) {"
                "x = x - 156;if (x > 147) then {"
                "read x;} else {"
                "print x;while (x > 148) {"
                "x = x - 158;if (x > 149) then {"
                "read x;} else {"
                "read y;while (x > 150) {"
                "x = x - 160;}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}";

        std::ofstream file;
        file.open(filename);
        file << sampleProgram;
        file.close();
        REQUIRE(std::filesystem::exists(filename));
        SourceProcessor sp = SourceProcessor(filename, pkbManager);
        sp.parseSIMPLE();
        sp.extractAndPopulate();

        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<ProcedureReader> procedureReader = pkbReaderManager->getProcedureReader();

        std::unordered_set<std::string> expectedProcName = { "deeplyNestedLogic" };
        REQUIRE(procedureReader->getAllProcedures() == expectedProcName);

        std::shared_ptr<StatementReader> statementReader = pkbReaderManager->getStatementReader();
        REQUIRE(statementReader->getAllStatements().size() == 376);

        auto end = std::chrono::high_resolution_clock::now();

        // Calculate duration
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // Output the duration
        std::cout << "LOG-INFO: Execution time for complex nested if-while source code: " << duration << " milliseconds" << std::endl;
    }

    SECTION("Stress 2") {
		auto start = std::chrono::high_resolution_clock::now();

		std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
		std::string filename = "sample.txt";
		std::string sampleProgram = 
            "procedure longAssign {"
            "n = g * t / n + h * l / x - d - m;"
            "print h;"
            "read l;"
            "read f;"
            "h = g % n * n / i - h / c * m / d * h % i * g / c % a / l + c / n / c - i - l;"
            "m = g * x % h + f - t + b + l * e % a - i + y;"
            "read k;"
            "k = f + g - x / i + d + i % x % z % h - e * x;"
            "y = c * n % y * z / k - h % g * a / d / b / e / n % f / c - d + n;"
            "e = a % z + f + b / x * c / d - z - z / x * k + m + n / d % a - b;"
            "print x;"
            "read i;"
            "read m;"
            "print l;"
            "print k;"
            "f = i * i / b + b + n / t % k - z / f / f % n - e / f * h * x - a % z - e * b * i;"
            "y = x + a % b + a % d - m - g / b * e % i % t % f - f % c;"
            "read y;"
            "t = x / d / e + c + f - a / z % d + e - f % g - h - b;"
            "b = b % e / l / c + z / y + a / b + d - y * g + f + c * g + g - m + n;"
            "y = n - y / a % c;"
            "read x;"
            "l = b * n + x % y + a % x % z + g / g % b % l * a - n / c / y - y % f % f;"
            "n = h % e / l * l % g + n - i / l - l - y % c;"
            "k = h - n % k * c / n * d * m * t;"
            "read h;"
            "x = f / d - m - x % x + k * h / g / i / x - t - t * g + z / m - a + m % z % n;"
            "print m;"
            "print b;"
            "read d;"
            "x = k / z + f / n % n / y * f + x + f - i % g + f;"
            "k = x * y / n * l + n + f + l - z + l * t - z + x * k;"
            "print g;"
            "d = f % y * i / h % x - b + z;"
            "h = b + z / f % f % x * i * b * e + c - i * z - f;"
            "print y;"
            "print l;"
            "l = l / d - m + f % l * y;"
            "c = b / a % m * x + t + h + n + m % e;"
            "a = g - i / c % y * a + y * z + t / t % h + n % f + e + d + g % m + g / t * k * n + h;"
            "print i;"
            "c = g / m * f + f * i % b + n;"
            "d = x % l / y + d % i / x / y * d / x - i / i % h - x * a + d * t + d % a % h;"
            "l = e / e % z * k - h / d + a;"
            "k = e / d - c - t * f + x % h / a % e;"
            "print f;"
            "read f;"
            "print t;"
            "print c;"
            "read z;"
            "print b;"
            "print g;"
            "m = m * m - l / t / x;"
            "n = e / c - t / f - h + t + k % x / g * x;"
            "m = z / z - y;"
            "m = e + k;"
            "print c;"
            "h = l * k % e % y;"
            "b = d % k + f + h % d % m - n + c / f * k * f + d + n;"
            "y = t % m % y * d * m % c / n + y * e % i / e * z / h % c - y % g * f * b * a + t;"
            "read b;"
            "n = d % c % i + k + i * h / k % d + y * i / l - i - x + m - g - f * b;"
            "print g;"
            "print t;"
            "read e;"
            "x = z + l / z % t % z % g % l + z / n + m % f * h % m / f + y / d + i - z / l - n / c;"
            "read t;"
            "print i;"
            "d = h - z + g - i;"
            "print m;"
            "f = d + z % a % k * k % m / i * f + h * n * a / z % l % d * y - d + l * e;"
            "n = b + c + n - m - z - y / b - y % h % y % z * e;"
            "e = n + a * d / n / h;"
            "d = z + h / e - g % l * t / x - f - b % x - z - l * c / c;"
            "t = c + g % d * i - x + b;"
            "print i;"
            "g = l - a;"
            "y = k * i + z % n % f * m - b - a / x % e / y - t % m * e % a + y / f % l;"
            "f = l * f * d / m;"
            "print d;"
            "t = e - d - c + t % f % y * e % k + l % x * c % d * c % a;"
            "print x;"
            "y = g + g + e * z;"
            "print z;"
            "d = y % y + d + y + k % x;"
            "n = n - g * b % m + c + c % m / e - b * d - d - n + i / h;"
            "y = y % t;"
            "print k;"
            "print c;"
            "i = h + d - x + a + g + i;"
            "c = f - e / a - y + x + d % c / i;"
            "read t;"
            "read m;"
            "m = g * g * z + x * h + x % k % b / d;"
            "b = k - b * a % t % l % f / e % l;"
            "read b;"
            "n = m - a + z - c / n * l % h / m % i * f - f / i * c % f - z + b * c % n + x;"
            "read n;"
            "e = h / t * d % z - d + n + c % a + k - z + d + a * e % t - x + y - m / g % e;"
            "g = k / z;"
            "d = m % d % a - b;"
            "n = f % c + z;"
            "print a;"
            "read a;"
            "f = y * z / c * m;"
            "read c;"
            "read k;"
            "read k;"
            "print y;"
            "read y;"
            "b = n - t - l / e + x % i / g - h % x * y * b / k / b * b / y * h % h + d % n;"
            "y = d + g - c / g * a - a;"
            "read n;"
            "z = d % c * d * i;"
            "h = c + a + y - a * z * t + z * h / c + b + t / z % l + y / c - m + x % f;"
            "h = y / g - y + t;"
            "x = d + c + f - n - d % c + g % m + d + m;"
            "f = x + n % l - y - d + c % l / m * c - l * i / g / c - b / d * t / a - t - a;"
            "print e;"
            "print a;"
            "read y;"
            "e = k - i - z % n / h / k;"
            "read y;"
            "read k;"
            "g = d % d / m / c % g * h + i * k + a + t;"
            "z = a - y - n % b % n;"
            "b = n - k + a + d + m;"
            "i = h % l - z % i % a + g * d % n;"
            "print l;"
            "i = z + n + z + d * b * m - c / d - z % m + d * m % d * g % l % z % f - l * y * g;"
            "h = h * b - f + h * e / l / i * h - b * c * i - n / x % x - e + a / a;"
            "read a;"
            "e = h % y * g + y + t + y * z % m - x - x;"
            "print d;"
            "k = g % y / i % c / b / l + b % c / c;"
            "print i;"
            "n = e * e / f % n / g * h / k - k - e / b - g - d / x + e - n - b - a % a % m + d;"
            "e = g / t % c - f / h % a + x * b + b - t + m + d;"
            "m = n - z - x * k / z % g / d * c % h + a + y % c * d + y + f + n * t % g + h + m;"
            "n = g + a;"
            "y = l / g - g * g + g - f / k / y % c;"
            "m = d - d % d / k / c;"
            "m = k * a % n * m * z * k % c;"
            "g = l + c - g % a - m + k + y;"
            "read n;"
            "d = k / y / y;"
            "read e;"
            "read e;"
            "z = y / g + i * k - f % z * b % b % y - k - b * b;"
            "print x;"
            "y = g * c / t % x / d * t - d + e % h - x - e % b - z / z;"
            "m = f - i % y % b + i - x - z * i - f - x + n % c / k * c * c / a % b;"
            "print g;"
            "d = a + f + a * m + x - z;"
            "read k;"
            "b = i / n + h / l * f - n - c + d - d / d - x - h / f * a - g % m * c + k;"
            "read z;"
            "print l;"
            "print n;"
            "read z;"
            "read d;"
            "read z;"
            "m = y % h % c * z - g * m * d + l / m + a / x / l % t * x - n + h * x + h - c - c * c;"
            "read c;"
            "print n;"
            "c = l - a + a * n % z + x % e % t - n - y + x % b;"
            "z = y % z + k / x;"
            "print x;"
            "read t;"
            "b = g % t;"
            "print f;"
            "c = b + n;"
            "print n;"
            "k = b / g / f * t * k / x % x * h / x + z % i - h / b * k % a + h * a % b / z - f - y;"
            "k = i * l - f - d / c % c - m - t - h + y % a - h % g / d / c * f % c - y % k;"
            "print c;"
            "g = f - z * m;"
            "i = k / i * x + f % m % h / k;"
            "z = a / m + x / g / c + z * a % a * a / c - x % c;"
            "n = e - n / g / n / n - i;"
            "print z;"
            "n = f % k % m * x * l / f * b / g - z;"
            "k = l % f - d + t - g % l + b - k / b % k / a * z + e + b * g / z % f + e - d + d * n;"
            "read y;"
            "print c;"
            "read f;"
            "print b;"
            "print c;"
            "read d;"
            "read m;"
            "print b;"
            "read e;"
            "print l;"
            "print b;"
            "read i;"
            "read e;"
            "f = t * i % a + k + k % b % h;"
            "t = x * t + z * d + e - d - g % y % z % e * c % m / g - f % h / a - d - a * b;"
            "c = d + f / c * k;"
            "c = t / y % f + y * t / c + m / b;"
            "}";

            std::ofstream file;
            file.open(filename);
            file << sampleProgram;
            file.close();
            REQUIRE(std::filesystem::exists(filename));
            SourceProcessor sp = SourceProcessor(filename, pkbManager);
            sp.parseSIMPLE();
            sp.extractAndPopulate();

            std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
            std::shared_ptr<ProcedureReader> procedureReader = pkbReaderManager->getProcedureReader();

            std::unordered_set<std::string> expectedProcName = { "longAssign" };
            REQUIRE(procedureReader->getAllProcedures() == expectedProcName);

            std::shared_ptr<StatementReader> statementReader = pkbReaderManager->getStatementReader();
            REQUIRE(statementReader->getAllStatements().size() == 200);

            auto end = std::chrono::high_resolution_clock::now();

            // Calculate duration
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

            // Output the duration
            std::cout << "LOG-INFO: Execution time for complex multi-assign source code: " << duration << " milliseconds" << std::endl;
    }

    SECTION("Stress 3") {
        auto start = std::chrono::high_resolution_clock::now();

        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram =
            "procedure proc1 {"
            "call proc13;  call proc5;  call proc18;  call proc10;  call proc4;  call proc3;  call proc15;  call proc14;  call proc16;  call proc24;  call proc12;  call proc9;  call proc6;  call proc2;  call proc19;  call proc21;  call proc11;  call proc22;}"
            "procedure proc2 {"
            "call proc10;  call proc15;  call proc5;  call proc9;  call proc18;  call proc17;  call proc24;  call proc14;  call proc4;  call proc21;  call proc20;  call proc16;  call proc8;  call proc3;  call proc7;  call proc23;  call proc6;  call proc11;  call proc25;  call proc22;  call proc19;}"
            "procedure proc3 {"
            "call proc7;  call proc17;  call proc6;  call proc4;  call proc8;}"
            "procedure proc4 {"
            "call proc6;  call proc16;  call proc18;  call proc19;  call proc22;  call proc14;  call proc8;  call proc7;  call proc21;  call proc23;  call proc9;  call proc11;}"
            "procedure proc5 {"
            "call proc17;  call proc21;  call proc13;  call proc25;  call proc10;  call proc16;  call proc24;  call proc7;  call proc23;  call proc20;}"
            "procedure proc6 {"
            "call proc19;  call proc14;  call proc18;  call proc9;  call proc8;  call proc10;  call proc23;  call proc21;  call proc12;  call proc17;  call proc24;  call proc16;  call proc20;}"
            "procedure proc7 {"
            "call proc14;  call proc24;  call proc20;  call proc17;  call proc19;  call proc23;  call proc8;  call proc15;  call proc10;  call proc18;  call proc13;  call proc16;  call proc12;  call proc22;  call proc25;  call proc21;  call proc11;  call proc9;}"
            "procedure proc8 {"
            "call proc15;  call proc17;  call proc23;  call proc22;  call proc11;  call proc16;  call proc14;}"
            "procedure proc9 {"
            "call proc16;  call proc23;  call proc18;  call proc12;  call proc13;  call proc15;  call proc24;  call proc11;  call proc10;  call proc19;  call proc21;  call proc17;  call proc22;  call proc20;}"
            "procedure proc10 {"
            "call proc23;  call proc25;  call proc15;  call proc18;  call proc21;  call proc17;  call proc13;  call proc11;  call proc12;}"
            "procedure proc11 {"
            "call proc19;  call proc14;  call proc24;  call proc25;  call proc21;  call proc17;}"
            "procedure proc12 {"
            "call proc16;  call proc25;  call proc20;  call proc23;  call proc18;  call proc19;  call proc21;  call proc14;  call proc15;  call proc17;  call proc22;  call proc13;  call proc24;}"
            "procedure proc13 {"
            "call proc16;  call proc15;  call proc22;}"
            "procedure proc14 {"
            "call proc23;  call proc25;  call proc20;  call proc21;  call proc19;}"
            "procedure proc15 {"
            "call proc19;}"
            "procedure proc16 {"
            "call proc22;  call proc18;  call proc23;  call proc19;  call proc17;  call proc20;}"
            "procedure proc17 {"
            "call proc21;  call proc25;  call proc22;  call proc20;}"
            "procedure proc18 {"
            "call proc23;  call proc20;  call proc21;  call proc22;  call proc24;  call proc25;}"
            "procedure proc19 {"
            "call proc25;  call proc21;  call proc20;  call proc24;}"
            "procedure proc20 {"
            "call proc21;  call proc22;  call proc25;  call proc23;  call proc24;}"
            "procedure proc21 {"
            "call proc23;}"
            "procedure proc22 {"
            "call proc24;}"
            "procedure proc23 {"
            "call proc24;  call proc25;}"
            "procedure proc24 {"
            "call proc25;}"
            "procedure proc25 {"
            "print x;"
            "}";


        std::ofstream file;
        file.open(filename);
        file << sampleProgram;
        file.close();
        REQUIRE(std::filesystem::exists(filename));
        SourceProcessor sp = SourceProcessor(filename, pkbManager);
        sp.parseSIMPLE();
        /*
        sp.extractAndPopulate();

        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<ProcedureReader> procedureReader = pkbReaderManager->getProcedureReader();

        std::unordered_set<std::string> expectedProcName = { "proc21", "proc9", "proc1", "proc20", "proc4", 
                                                          "proc25", "proc22", "proc23", "proc24", "proc14",
                                                          "proc11", "proc17", "proc18", "proc19", "proc15", "proc13", "proc16",
                                                          "proc2", "proc12", "proc5", "proc10", "proc6", "proc7", "proc8", "proc3",};
        REQUIRE(procedureReader->getAllProcedures() == expectedProcName);
        */
        auto end = std::chrono::high_resolution_clock::now();

        // Calculate duration
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // Output the duration
        std::cout << "LOG-INFO: Execution time for complex multi-call-procedure source code: " << duration << " milliseconds" << std::endl;
    }
}

#endif
