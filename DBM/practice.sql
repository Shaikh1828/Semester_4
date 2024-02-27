-- select employee_id, last_name, job_id, department_id
-- from employees
-- where department_id = 90 ;

-- select employee_id, last_name, job_id, department_id
-- from employees
-- where last_name = 'Whalen' ;

-- select employee_id, last_name, job_id, department_id
-- from employees
-- where hire_date = '17-FEB-96' ;

-- SELECT last_name, salary
-- FROM employees
-- WHERE salary <= 3000 ;

-- SELECT last_name, salary
-- FROM employees
-- WHERE salary BETWEEN 2500 AND 3500 ;

-- SELECT employee_id, last_name, salary, manager_id
-- FROM employees
-- WHERE manager_id IN (100, 101, 201) ;

-- SELECT first_name
-- FROM employees
-- WHERE frist_name LIKE 'S%' ;

-- SELECT last_name
-- FROM employees
-- WHERE last_name LIKE '_o%' ;

-- SELECT first_name, manager_id
-- FROM employees
-- WHERE manager_id IS NULL ;

-- SELECT employee_id, last_name, manager_id, salary
-- FROM employees
-- WHERE salary >= 10000 
--   AND job_id LIKE '%MAN%' ;

-- SELECT employee_id, last_name, manager_id, salary
-- FROM employees
-- WHERE salary >= 10000 
--    OR job_id LIKE '%MAN%' ;

-- SELECT last_name, job_id
-- FROM employees
-- WHERE job_id
--   NOT IN ('IT_PROG', 'ST_CLERK', 'SA_REP') ;

-- SELECT last_name, job_id, salary
-- FROM employees
-- WHERE job_id = 'SA_REP'
--    OR job_id = 'AD_REP'
--   AND salary >= 15000 ;

-- SELECT last_name, job_id, salary
-- FROM employees
-- WHERE ( job_id = 'SA_REP'
--    OR job_id = 'AD_REP' )
--   AND salary >= 15000 ;

-- SELECT last_name, job_id, department_id, hire_date
-- FROM employees
-- ORDER BY hire_date ;

-- SELECT last_name, job_id, department_id, hire_date
-- FROM employees
-- ORDER BY hire_date DESC ;

-- SELECT employee_id, last_name, salary*12 Annsal
-- FROM employees
-- ORDER BY Annsal ;

-- SELECT last_name, job_id, department_id, hire_date
-- FROM employees
-- ORDER BY 3 ;

-- SELECT last_name, department_id, salary
-- FROM employees
-- ORDER BY department_id, salary DESC ;

-- SELECT employee_id, last_name, salary, department_id
-- FROM employees
-- WHERE employee_id = &employee_num ;

-- SELECT last_name, department_id, salary*12
-- FROM employees
-- WHERE job_id = '&job_title' ;

