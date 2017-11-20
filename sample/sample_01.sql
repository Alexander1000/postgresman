--insert correct
insert into schema.some_table (id, name, value) values (13, 'Alexander O''realy', '0xffff');

/*
some comments in this place
***** !!! /* **** !!!! * /
*/

-- insert syntax error
insert schema.some_table (id, name, value) values (13, 'Alexander', '0xffff');
