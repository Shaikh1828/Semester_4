connect system

create user test identified by test account unlock;

alter user test identified by test account unlock;

grant dba to test;

connect test

-- @G:\Semester_4\DBM\connect.sql