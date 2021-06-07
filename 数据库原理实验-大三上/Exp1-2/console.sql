-- Exp2 Part

create database student_test character set utf8;

use student_test;

create table StudentInfo (
    StuNum int not null,
    Name char(10) null,
    Gender char(2) null,
    Birth datetime null check ( Birth < sysdate() ),
    ClassNum int not null,
    Depart char(20) not null ,
    ChosenClass1 char(20) null,
    ChosenClass2 char(20) null
);

create table CourseInfo (
    ClassNum int not null,
    Name char(20) null,
    ForDepart char(20) null,
    Capacity int not null,
    Point float(3, 2) not null
);

alter table StudentInfo modify column Gender char(2) null check ( Gender in ('男', '女') );
alter table CourseInfo modify column Capacity int not null check ( Capacity < 100 );


-- Exp2 Book Part, 6
drop database student_book;

create database student_book character set utf8;

use student_book;

create table Student (
    Sno int not null primary key,
    Sname char(10) null,
    Ssex char(2) null check ( Ssex in ('男', '女') ),
    Sage int null check ( Sage < 30 ),
    Sdept char(10) not null,
    Sclass int not null
);

create table Course (
    Cno int not null primary key,
    Cname char(20) null,
    Cpo int null,
    Ccredit int not null check ( Ccredit < 10 )
);

create table SC (
    Sno int not null,
    Cno int not null,
    Grade int null check ( Grade <= 100 )
);

INSERT INTO Student (Sno, Sname, Ssex, Sage, Sdept, Sclass) VALUES (201215121, '李勇', '男', 20, 'CS', 1);
INSERT INTO Student (Sno, Sname, Ssex, Sage, Sdept, Sclass) VALUES (201215122, '刘晨', '女', 19, 'CS', 2);
INSERT INTO Student (Sno, Sname, Ssex, Sage, Sdept, Sclass) VALUES (201215123, '王敏', '女', 18, 'MA', 1);
INSERT INTO Student (Sno, Sname, Ssex, Sage, Sdept, Sclass) VALUES (201215125, '张立', '男', 19, 'IS', 2);

INSERT INTO Course (Cno, Cname, Cpo, Ccredit) VALUES (1, '数据库', 5, 4);
INSERT INTO Course (Cno, Cname, Cpo, Ccredit) VALUES (2, '数学', NULL, 2);
INSERT INTO Course (Cno, Cname, Cpo, Ccredit) VALUES (3, '信息系统', 1, 4);
INSERT INTO Course (Cno, Cname, Cpo, Ccredit) VALUES (4, '操作系统', 6, 3);
INSERT INTO Course (Cno, Cname, Cpo, Ccredit) VALUES (5, '数据结构', 7, 4);
INSERT INTO Course (Cno, Cname, Cpo, Ccredit) VALUES (6, '数据处理', NULL, 2);
INSERT INTO Course (Cno, Cname, Cpo, Ccredit) VALUES (7, 'PASCAL语言', 6, 4);

INSERT INTO SC (Sno, Cno, Grade) VALUES (201215121, 1, 92);
INSERT INTO SC (Sno, Cno, Grade) VALUES (201215121, 2, 85);
INSERT INTO SC (Sno, Cno, Grade) VALUES (201215121, 3, 88);
INSERT INTO SC (Sno, Cno, Grade) VALUES (201215122, 2, 90);
INSERT INTO SC (Sno, Cno, Grade) VALUES (201215122, 3, 80);

-- 7.1
select Sname, Sage from Student where Sname like '王%' order by Sage desc;

-- 7.2
select Sname, Sno from Student where (select AVG(Grade) from SC where Cno = 1) > 80 group by Sname, Sno;

-- 7.3
select Student.Sclass, Course.Cname, count(SC.Sno), avg(SC.Grade) from Student, Course, SC where SC.Sno = Student.Sno group by Student.Sclass, Course.Cname;

-- 7.4
select Cname from Course where Cno not in (select Cno from SC where Sno = (select Sno from Student where Sname = '李勇'));


-- Website Part
drop database empmanage;

create database empmanage character set utf8;
use empmanage;
create table admin (
    id char(20) not null primary key,
    password char(32) not null
);
insert into admin(id, password) values ("admin", md5("passwd1234"));