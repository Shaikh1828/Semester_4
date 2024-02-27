CREATE TABLE branch (
	branch_name VARCHAR2(25),
	branch_city VARCHAR2(25),
	assets NUMBER(15),
	CONSTRAINT branch_pk PRIMARY KEY (branch_name)
);

CREATE TABLE customer (
	customer_name VARCHAR2(30),
	customer_street VARCHAR2(30),
	customer_city VARCHAR2(20),
	CONSTRAINT customer_pk PRIMARY KEY (customer_name)
);

CREATE TABLE account (
	account_number NUMBER(15),
	branch_name VARCHAR2(25),
	balance NUMBER(15),
	CONSTRAINT account_pk PRIMARY KEY (account_number),
	CONSTRAINT account_fk FOREIGN KEY (branch_name) REFERENCES branch (branch_name)
);


CREATE TABLE loan (
	loan_number NUMBER(15),
	branch_name VARCHAR2(25),
	amount NUMBER(10),
	CONSTRAINT loan_pk PRIMARY KEY (loan_number),
	CONSTRAINT loan_fk FOREIGN KEY (branch_name) REFERENCES branch (branch_name)
);

CREATE TABLE depositor (
	customer_name VARCHAR2(30),
	account_number NUMBER(15),
	CONSTRAINT depositor_pk PRIMARY KEY (customer_name,account_number),
	CONSTRAINT depositor_customer_fk FOREIGN KEY (customer_name) REFERENCES customer (customer_name),
	CONSTRAINT depositor_account_fk FOREIGN KEY (account_number) REFERENCES account (account_number)
);

CREATE TABLE borrower (
	customer_name VARCHAR2(30),
	loan_number NUMBER(15),
	CONSTRAINT borrower_pk PRIMARY KEY (customer_name,loan_number),
	CONSTRAINT borrower_customer_fk FOREIGN KEY (customer_name) REFERENCES customer (customer_name),
	CONSTRAINT borrower_loan_fk FOREIGN KEY (loan_number) REFERENCES loan (loan_number)	
);

-- @G:\Semester_4\DBM\create_table.sql