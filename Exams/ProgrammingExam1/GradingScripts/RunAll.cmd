@echo off
call vcvars32.bat

SET total_number_of_tests= 4
SET current_test_number= 0
SET total_percentage= 0
SET message=

:PRE_TEST
SET /A current_test_number= %current_test_number% + 1
SET message= Result
GOTO TEST%current_test_number%

:TEST1
echo running test 1
call Run-test.cmd main_test1 output_test1.txt
IF %RETURNVALUE% neq 0 ( GOTO FAIL ) ELSE ( GOTO PASS )

:TEST2
echo running test 2
call Run-test.cmd main_test2 output_test2.txt
IF %RETURNVALUE% neq 0 ( GOTO FAIL ) ELSE ( GOTO PASS )

:TEST3
echo running test 3
call Run-test.cmd main_test3 output_test3.txt
IF %RETURNVALUE% neq 0 ( GOTO FAIL ) ELSE ( GOTO PASS )

:TEST4
echo running test 4
call Run-test.cmd main_test4 output_test4.txt
IF %RETURNVALUE% neq 0 ( GOTO FAIL ) ELSE ( GOTO PASS )

:FAIL
if %RETURNVALUE% equ 1 SET message= %message%: BUILD_FAIL
if %RETURNVALUE% equ 2 SET message= %message%: DIFF_FAIL
if %RETURNVALUE% equ 3 SET message= %message%: MEMORY_LEAK
if %RETURNVALUE% equ 4 SET message= %message%: DIFF_AND_LEAK
GOTO DONE


:PASS
echo %message%: PASSED
@echo off
IF %current_test_number% equ %total_number_of_tests% ( GOTO TABLEN ) ELSE ( GOTO PRE_TEST )

:TABLEN
echo running tablen
tablen.exe myArray.cpp > tablen_out.txt
for /f %%i in ("tablen_out.txt") do set size=%%~zi
if %size% gtr 0 ( GOTO TABLEN_FAIL ) ELSE ( GOTO TABLEN_PASSED )

tablen.exe myArray.h > tablen_out.txt
for /f %%i in ("tablen_out.txt") do set size=%%~zi
if %size% gtr 0 ( GOTO TABLEN_FAIL ) ELSE ( GOTO TABLEN_PASSED )

:TABLEN_FAIL
echo Result: FAILED
echo ************************************************  
del tablen_out.txt
GOTO DONE

:TABLEN_PASSED
echo Result: PASSED
echo ************************************************  
del tablen_out.txt

:DONE

pause
@echo on