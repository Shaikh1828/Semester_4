-- SELECT T.BRANCH_NAME
-- FROM BRANCH T, BRANCH S
-- WHERE S.BRANCH_CITY = 'BROOKLYN'
-- AND T.ASSETS > S.ASSETS;


-- List in alphabetic order the names of all customers 
-- having a loan in Perryridge branch

-- SELECT B.CUSTOMER_NAME
-- FROM BORROWER B, LOAN L
-- WHERE B.LOAN_NUMBER = L.LOAN_NUMBER
-- AND L.BRANCH_NAME = 'PERRYRIDGE'
-- ORDER BY CUSTOMER_NAME;

--Find the number of depositors for each branch.

-- SELECT BRANCH_NAME, COUNT(DISTINCT CUSTOMER_NAME) NUM_DEP
-- FROM ACCOUNT A, DEPOSITOR D
-- WHERE A.ACCOUNT_NUMBER = D.ACCOUNT_NUMBER
-- GROUP BY BRANCH_NAME;

-- Find the names of all branches where 
-- the average account balance is more than $1,200.

-- SELECT BRANCH_NAME, AVG(A.BALANCE)
-- FROM ACCOUNT A
-- GROUP BY BRANCH_NAME
-- HAVING AVG(A.BALANCE) > 500;

-- Find all customers who have both an account 
-- and a loan at the bank.

-- SELECT DISTINCT D.CUSTOMER_NAME
-- FROM DEPOSITOR D, BORROWER B
-- WHERE D.CUSTOMER_NAME = B.CUSTOMER_NAME;

-- SELECT DISTINCT CUSTOMER_NAME
-- FROM DEPOSITOR
-- WHERE CUSTOMER_NAME IN (SELECT CUSTOMER_NAME
--                         FROM BORROWER);

--    Find all customers who have a loan at 
--    the bank but do not have an account at the bank

-- SELECT CUSTOMER_NAME
-- FROM BORROWER
-- WHERE CUSTOMER_NAME NOT IN(SELECT CUSTOMER_NAME FROM DEPOSITOR);


-- Find all customers who have both an 
-- account and a loan at the Perryridge branch

-- SELECT CUSTOMER_NAME
-- FROM BORROWER B, LOAN L
-- WHERE B.LOAN_NUMBER = L.LOAN_NUMBER
-- AND L.BRANCH_NAME = 'PERRYRIDGE'
-- AND CUSTOMER_NAME IN(SELECT CUSTOMER_NAME
--                     FROM DEPOSITOR D, ACCOUNT A
--                     WHERE D.ACCOUNT_NUMBER = A.ACCOUNT_NUMBER
--                     AND A.BRANCH_NAME = 'PERRYRIDGE');

-- Find all branches that have greater 
-- assets than some branch located in Brooklyn.

-- SELECT BRANCH_NAME, ASSETS
-- FROM BRANCH
-- WHERE ASSETS > SOME(SELECT ASSETS
--                     FROM BRANCH
--                     WHERE BRANCH_CITY = 'BROOKLYN');


-- Find the names of all branches that 
-- have greater assets than all branches located in Brooklyn.

-- SELECT BRANCH_NAME, ASSETS
-- FROM BRANCH
-- WHERE ASSETS > ALL(SELECT ASSETS
--                     FROM BRANCH
--                     WHERE BRANCH_CITY = 'BROOKLYN');


-- Find all customers who have an account 
-- at all branches located in Brooklyn.

select distinct S.customer_name
from depositor as S
where not exists (		
                (select branch_name
                from branch
                where branch_city = 'Brooklyn') 
                except
                (select R.branch_name
                from depositor as T, account as R
                where T.account_number = R.account_number and
                S.customer_name = T.customer_name ));

