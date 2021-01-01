drop database `exp3`;

create database `exp3` character set `utf8`;

use `exp3`;

create table `student`
(
    `Number` int not null primary key,
    `Name` char(10) null,
    `Gender` char(2) null check ( Gender in ('男', '女') ),
    `Birth` date null check ( Birth < sysdate() ),
    `Major` char(20) null,
    `Class` int not null
);

create table `course`
(
    `Number` int not null primary key,
    `Name` char(20) null,
    `Credit` float not null,
    `Capacity` int not null check ( Capacity <= 100 )
);

create table `course_teacher`
(
    `CourseNum` int not null,
    foreign key (`CourseNum`) references course(`Number`),
    `Teacher` char(10) not null
);

create table `course_choose`
(
    `StudentNum` int not null,
    foreign key (`StudentNum`) references student(`Number`),
    `CourseNum` int not null,
    foreign key (`CourseNum`) references course(`Number`),
    `Teacher` char(10) not null,
    `Grade` float not null
);

create trigger teacher_check before insert on course_choose for each row
    begin
        if NEW.Teacher not in (select Teacher from course_teacher where course_teacher.CourseNum = NEW.CourseNum) then
            signal sqlstate 'HY000' set message_text = 'Teacher非法';
        end if;
    end;

create table `user` (
    `Username` char(20) not null primary key,
    `Email` char(30) null,
    `Homepage` char(100) null,
    `Telephone` char(15) null,
    `Address` char(100) null
);

create table `bbs`
(
    `ID` int not null primary key auto_increment,
    `Username` char(20) not null,
    `Title` char(50) not null,
    `Content` varchar(500) not null,
    foreign key (`Username`) references user(`Username`)
)
auto_increment = 1;

create table `bbs_reply`
(
    `ID` int not null primary key auto_increment,
    `BBSID` int not null,
    foreign key (`BBSID`) references bbs(`ID`),
    `Username` char(20) not null,
    `ReplyContent` varchar(500) not null,
    foreign key (`Username`) references user(`Username`)
)
auto_increment = 1;


-- 插入示例数据
insert into student(Number, Name, Gender, Birth, Major, Class)
values
       (20201001, '冠逸致', '男', '2000-01-01', '计算机', 1),
       (20201110, '务忆南', '女', '2001-09-09', '机械', 1),
       (20200207, '祁麦冬', '女', '2000-10-01', '自动化', 3),
       (20201011, '张弘博', '男', '2000-11-01', '计算机', 1),
       (20201005, '干文君', '女', '2000-04-23', '计算机', 2),
       (20202002, '长勇军', '男', '2000-01-01', '外国语', 2),
       (20200101, '习元洲', '男', '2000-05-10', '通信', 1),
       (20200911, '潜雨竹', '女', '2000-04-04', '网络安全', 3)
;

insert into course(Number, Name, Credit, Capacity)
values
       (1000, '数据库', 3.0, 100),
       (1002, '计算机组成原理', 4.0, 100),
       (1001, '操作系统', 3.0, 50),
       (1004, 'C语言程序设计', 2.0, 30),
       (1010, '汉语语言学', 5.0, 50),
       (1008, '高等数学', 5.0, 70),
       (3012, '机械设计实践', 0.5, 10)
;

-- Violation Test
insert into course(Number, Name, Credit, Capacity) value (2000, '线性代数', 3.0, 120);

insert into course_teacher(CourseNum, Teacher)
values
       (1000, '钟娅欣'),
       (1002, '狂浩'),
       (1000, '吕运发'),
       (1008, '蔚顺'),
       (1010, '业沈然'),
       (1002, '礼东'),
       (3012, '习昊宇'),
       (1004, '张雄')
;

-- Violation Test
insert into course_teacher(CourseNum, Teacher) value (1005, '仁平凡');

insert into course_choose(StudentNum, CourseNum, Teacher, Grade)
values
       (20201005, 1000, '吕运发', 70),
       (20201005, 1002, '狂浩', 95.5),
       (20200207, 1000, '钟娅欣', 59),
       (20201011, 1002, '狂浩', 85),
       (20201011, 1008, '蔚顺', 86.5),
       (20201011, 1004, '张雄', 54.0)
;

-- Violation Test
insert into course_choose(StudentNum, CourseNum, Teacher, Grade) value (20201005, 1000, '堂秋白', 1);

insert into user(Username, Email, Homepage, Telephone, Address)
values
       ('lvyunfa', 'lvyunfa@hdu.edu.cn', '', '13800234567', ''),
       ('wuyinan007', 'wuyn_hdu@163.com', 'https://www.hereiswuyinan.com/', '17644523000', 'Hangzhou'),
       ('kh123', 'kh@live.com', '', '', '')
;

insert into bbs(ID, Username, Title, Content)
values (1, 'kh123', '街舞社招新', '一年一度的街舞社招新火热来袭！\n还在等什么？\n戳下方链接填写报名表\nhttps://mp.weixin.com/abcde'),
       (2, 'wuyinan007', '报名杭电十佳歌手大赛啦！', '迫不及待想让大家听到我的歌声了，我会好好加油的！'),
       (3, 'lvyunfa', '杭电十佳歌手大赛，等你来参赛', '要报名的同学可扫描下方二维码，了解详情，或电话联系+8613800234567\n<img src=\'qr.jpg\'>')
;

insert into bbs_reply(ID, BBSID, Username, ReplyContent)
values (1, 2, 'kh123', '什么？你也去？那我去给你打call'),
       (2, 2, 'lvyunfa', '感谢支持我们的工作！'),
       (3, 1, 'wuyinan007', '想去可惜身材不够啊～')
;

-- Exp Begin
-- 4.1
select student.Number, student.Name, course.Name, course_choose.Grade
from student,
     course,
     course_choose
where (course_choose.StudentNum = Student.Number)
  and (course.Number = course_choose.CourseNum);


-- 4.2
select Number, Name
from student
where student.Number in (select StudentNum
                         from course_choose
                         where CourseNum in (select Number from course where Name = '数据库'));


-- 4.3
select student.Number, student.Name, course.Number, course.Name, course_choose.Grade
from student,
     course,
     course_choose
where (course.Number = course_choose.CourseNum)
  and (student.Number = course_choose.StudentNum)
  and (course_choose.Grade in
       (select Grade from course_choose where Grade <= 60)
    );


-- 4.4
select Teacher from course_choose
where StudentNum = (
    select Number from student where Name = '张弘博'
    );


-- 4.5
select Name, Number from student
where Number = (
    select StudentNum from course_choose
    where Grade = (
        select MAX(Grade) from course_choose where Teacher = '狂浩'
        )
    );


-- 4.6
select user.*, bbs.Title from user, bbs
where user.Username = bbs.Username and bbs.Title like '%杭电十佳歌手%';


-- 4.7(1)
select bbs.Title, bbs.Content,bbs_reply.ReplyContent from bbs, bbs_reply
where bbs_reply.BBSID = bbs.ID and bbs.Title like '%杭电十佳歌手%';


-- 4.7(2)
select bbs.Title, COUNT(bbs_reply.ID) from bbs, bbs_reply
where bbs_reply.BBSID = bbs.ID
group by bbs.Title
order by COUNT(bbs_reply.ID) DESC;

-- 5.2
create view Class1 as (select student.Number, student.Name, student.Class, course_choose.CourseNum, course_choose.Grade
    from student, course_choose
    where course_choose.StudentNum = student.Number
    and Student.Class = 1
    );

select Number, Name, AVG(Grade) from Class1 where Name = '张弘博' group by Number, Name;