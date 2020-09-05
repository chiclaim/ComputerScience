
## 登录 mysql

安装后登录Mysql，以 root 用户为例：

```
mysql -u root -p
```

## 数据定义

### 创建数据库

```

create database mysql_test default charset utf8 collate utf8_general_ci
```

`collate` 类型来告知 mysql 如何对该列进行排序和比较。简而言之，COLLATE会影响到 **ORDER BY** 语句的顺序，会影响到WHERE条件中大于小于号筛选出来的结果，会影响 **DISTINCT**、**GROUP BY**、**HAVING** 语句的查询结果。另外，mysql建索引的时候，如果索引列是字符类型，也会影响索引创建，只不过这种影响我们感知不到。总之，凡是涉及到字符类型比较或排序的地方，都会和COLLATE有关。

`utf8_unicode_ci`，其实是用来排序的规则。很多 COLLATE 都带有 `_ci` 字样，这是 `Case Insensitive` 的缩写，即大小写无关，也就是说"A"和"a"在排序和比较的时候是一视同仁的。`selection * from table1 where field1="a"` 同样可以把 field1 为 "A" 的值选出来。与此同时，对于那些 `_cs` 后缀的 `COLLATE`，则是 `Case Sensitive`，即大小写敏感的。

>这里顺便讲个题外话，mysql中有utf8和utf8mb4两种编码，在mysql中请大家忘记**utf8**，永远使用**utf8mb4**。这是mysql的一个遗留问题，mysql中的utf8最多只能支持3bytes长度的字符编码，对于一些需要占据4bytes的文字，mysql的utf8就不支持了，要使用utf8mb4才行。


可以通过 `show collation` 命令列出 mysql 支持的所有 collation.

创建完数据库后，可以通过 `show databases` 列表所有的数据库



使用 mysql_test 数据库：

```
use mysql_test;
```

查看 mysql_test 数据库的定义：

```
show create database mysql_test

+------------+--------------------------------------------------------------------------------------------------------+
| Database   | Create Database                                                                                        |
+------------+--------------------------------------------------------------------------------------------------------+
| mysql_test | CREATE DATABASE `mysql_test` /*!40100 DEFAULT CHARACTER SET utf8 */ /*!80016 DEFAULT ENCRYPTION='N' */ |
+------------+--------------------------------------------------------------------------------------------------------+
```

修改 mysql_test 数据库

```

// 将字符集改成 gb2313
alter database mysql_test default charset gb2312 default collate gb2312_chinese_ci;

// 查看修改是否生效
show create database mysql_test;
+------------+----------------------------------------------------------------------------------------------------------+
| Database   | Create Database                                                                                          |
+------------+----------------------------------------------------------------------------------------------------------+
| mysql_test | CREATE DATABASE `mysql_test` /*!40100 DEFAULT CHARACTER SET gb2312 */ /*!80016 DEFAULT ENCRYPTION='N' */ |
+------------+----------------------------------------------------------------------------------------------------------+

```

删除数据库：

```
drop database mysql_test;
```

### 创建表

```
create table customers
    (
    id int not null auto_increment,
    name char(50) not null,
    sex char(1) not null default 0,
    address char(50) null ,
    contact char(50)null,
    primary key(id)
    );
```
- auto_increment 自增长
- default 设置默认值
- primary key 设置主键

### 查看表的定义

```
show create table customers;

| customers | CREATE TABLE `customers` (
  `id` int NOT NULL,
  `name` char(50) NOT NULL,
  `gender` char(1) DEFAULT '1',
  `address` char(50) DEFAULT NULL,
  `contact` char(20) DEFAULT NULL,
  PRIMARY KEY (`id`,`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 |
```

### 查看表的结构

```
desc customers;
+---------+----------+------+-----+---------+-------+
| Field   | Type     | Null | Key | Default | Extra |
+---------+----------+------+-----+---------+-------+
| id      | int      | NO   | PRI | NULL    |       |
| name    | char(50) | NO   | PRI | NULL    |       |
| gender  | char(1)  | YES  |     | 1       |       |
| address | char(50) | YES  |     | NULL    |       |
| contact | char(20) | YES  |     | NULL    |       |
+---------+----------+------+-----+---------+-------+

```

### 更新表

通过 alter table 修改表。

#### add column 子句

```
alter table customers add column city0 char(10) not null default 'HangZhou' after city1;
```

add column 子句后面与创建表的语法差不多。`after` 表示创建的列表在 sex 列之后。与之对应 `first`，表示第一列，后面不跟列名


#### change column 子句

```
// 修改列名字、数据类型、默认值、列位置
alter table customers change column sex gender char(1) default 1 first;
```

### alter column 子句

```
// 修改列的默认值
alter table customers alter column gender set default '0';
```

#### modify column 子句

```
// 修改列的数据类型、列位置
alter table customers modify column contact char(20) first;
```

#### rename to 子句

```
alter table customers rename to customer;

// 也可以通过 rename table ...
rename table customer to customers;
````
#### drop 子句

```
// 删除列
alter table customers drop column city;

// 删除主键
alter table customers drop primary key;

// 删除外键
alter table customers drop foreign key fk_name;

// 删除索引
alter table customers drop index index_name;

```


#### add primary key 子句

```
alter table customers add primary key(id,name)
```

#### add forerign key 子句

```
alter table customers add foreign key fk_seller_id(seller_id) references seller(id);
```




### 创建索引

索引分为：
- 普通索引（index）
- 唯一索引（unique）
- 主键索引（primary key）

通常将 WHERE 子句和 JOIN 子句出现的列来作为索引列。

创建索引的时候还可以指定列的前几个字符作为索引，使用列的一部分作为索引有利于减少索引文件的大小，节省磁盘空间。

语法：

```
CREATE [UNIQUE] INDEX index_name ON table_name(index_column_name,...)

index_column_name 格式：index_column_name(length)[ASC | DESC]

```


#### create index 语句创建索引

```
// contact 列的前三个字符为索引
create index index_c on customers(contact(3) asc);
```

#### create table 时创建索引

```
CREATE TABLE `customers` (
  `id` int NOT NULL,
  `name` char(50) NOT NULL,
  `gender` char(1) DEFAULT '1',
  `address` char(50) DEFAULT NULL,
  `contact` char(20) DEFAULT NULL,
  PRIMARY KEY (`id`,`name`),
  INDEX `index_c` (`contact`(3))
);
```

#### alter table 创建索引

```
alter table customers add index index_c(contact(3));
```


#### 查看索引

```
show index from customers;
```


## 数据的更新


### 插入

```
// insert ... values ...
insert into customers(name,gender,address,contact) values('chiclaim','1','HZ','18312345678');

// insert ... set ...
insert into customers set name='Johnny',gender = '0',address='SZ',contact='110';


// insert ... select...
insert into customers(columns...) select ....
```

### 删除

```
// 语法
delete from table_name [where condition] [order by ...][limit row_count]

// 删除所有记录
delete from customers;

// 根据条件删除
delete from customers where id = 1;
```


### 修改

```
//语法：
update table_name set columnName = {expre|DEFAULT} [,columnName = {expre|DEFAULT}] ... [where condition] [order by] [limit row_count]

//将id为2的性别改成1
update customers set gender='1' where id = 2;

```

## 查询

### 查询指定的列

```
// 查询所有记录
select * from customers;

// 查询特定列
select name,contact from customers;
```

### 定义并使用别名

```
select name as 姓名,contact as  联系电话 from customers;
+----------+--------------+
| 姓名     | 联系电话     |
+----------+--------------+
| chiclaim | 18112345678  |
+----------+--------------+
```
### 替换查询结果集中的数据

```
select name as 姓名,
    case 
    when gender = '0' then '女'
    else '男'
    end as 性别, contact as 联系电话
from customers;

+----------+--------+--------------+
| 姓名     | 性别   | 联系电话     |
+----------+--------+--------------+
| chiclaim | 男     | 18112345678  |
+----------+--------+--------------+

```



### 计算列值

```
select name ,id+100 from customers;
```

### 聚合函数


常用的聚合函数：

函数名 | 说明
---|---
count | 求组中项数
max | 求最大值
min | 求最小值
avg | 求平均值


### from 子句与多表连接查询

#### 交叉连接

交叉连接又称 `笛卡尔积`，一张表的每一行和另一张表的每一行的笛卡尔乘积。

交叉连接返回的查询结果集的记录行数等于其所连接的两张表记录行数的乘积。例如下面的例子输出为 6 行：

```
// 3条记录
select * from customers;
+----+----------+--------+---------+-------------+-----------+
| id | name     | gender | address | contact     | seller_id |
+----+----------+--------+---------+-------------+-----------+
|  5 | YZQ      | 1      | ZJ      | 18112345678 |         1 |
|  6 | chiclaim | 1      | CH      | 18312345678 |         1 |
|  7 | Johnny   | 1      | CH      | 17312345678 |         1 |
+----+----------+--------+---------+-------------+-----------+

// 2条记录
select * from seller;
+----+------+
| id | name |
+----+------+
|  1 | Pony |
+----+------+

// 交叉乘积为 3*2 = 6 行
select * from customers cross join seller;
+----+----------+--------+---------+-------------+-----------+----+------+
| id | name     | gender | address | contact     | seller_id | id | name |
+----+----------+--------+---------+-------------+-----------+----+------+
|  5 | YZQ      | 1      | ZJ      | 18112345678 |         1 |  1 | Pony |
|  5 | YZQ      | 1      | ZJ      | 18112345678 |         1 |  2 | Jack |
|  6 | chiclaim | 1      | CH      | 18312345678 |         1 |  1 | Pony |
|  6 | chiclaim | 1      | CH      | 18312345678 |         1 |  2 | Jack |
|  7 | Johnny   | 1      | CH      | 17312345678 |         1 |  1 | Pony |
|  7 | Johnny   | 1      | CH      | 17312345678 |         1 |  2 | Jack |
+----+----------+--------+---------+-------------+-----------+----+------+

```

#### 内连接

内连接是一种最为常见的连接类型，内联接利用条件判断表达式中的比较运算符来组合两张表的记录，其目的是为了消除`交叉连接`中的某些数据。

```
select * from customers inner join seller on customers.seller_id = seller.id;
+----+----------+--------+---------+-------------+-----------+----+------+
| id | name     | gender | address | contact     | seller_id | id | name |
+----+----------+--------+---------+-------------+-----------+----+------+
|  5 | YZQ      | 1      | ZJ      | 18112345678 |         1 |  1 | Pony |
|  6 | chiclaim | 1      | CH      | 18312345678 |         1 |  1 | Pony |
|  7 | Johnny   | 1      | CH      | 17312345678 |         1 |  1 | Pony |
+----+----------+--------+---------+-------------+-----------+----+------+
```

内连接是系统默认的表连接方式，所以可以省略 `inner` 关键字。

内连接通常有三种形式：
- 等值连接
即在 on 子句中使用 = 进行相等性测试。通常等值连接会包含一个主键和一个外键。 
- 非等值连接
即在 on 子句中使用 = 以外的比较运算符进行测试。
- 自连接
将一个表与自身进行连接。需要为表指定两个不同的别名。

#### 外连接

内连接是在交叉连接的结果上返回满足条件的记录。

但有时也会存在输出不满足连接条件的元组信息的查询需求。这种情况就需要使用外连接来实现。

外连接是首先将连接的两张表分为基表和参考表，然后在以基表为依据返回满足和不满足的条件记录。

外连接可以在表中没有匹配记录的情况下仍然返回记录，外连接要比内连接更加注重两张表的关系，其根据连接的顺序可分为左连接和有连接：

- 左连接（left outer join）
    
    用左表（基表）的所有行与右表（参考表）进行匹配，即匹配左表中的每一行及右表中符合条件的行。
    在左连接的结果集中除了匹配的行，还包括基表有的，但参考表中没有的行，参考表中没有的行则置为 null

    ```
    select * from customers left outer join seller on customers.seller_id = seller.id;
    +----+----------+--------+---------+-------------+-----------+------+------+
    | id | name     | gender | address | contact     | seller_id | id   | name |
    +----+----------+--------+---------+-------------+-----------+------+------+
    |  5 | YZQ      | 1      | ZJ      | 18112345678 |         1 |    1 | Pony |
    |  6 | chiclaim | 1      | CH      | 18312345678 |         1 |    1 | Pony |
    |  7 | Johnny   | 1      | CH      | 17312345678 |         1 |    1 | Pony |
    +----+----------+--------+---------+-------------+-----------+------+------+
    
    ```

- 右连接（right outer join）
    
    连接方式和左连接是类似的，只不过基表标称了右表，参考表是左表。
    在、右连接的结果集中除了匹配的行，还包括基表有的，但参考表中没有的行，参考表中没有的行则置为 null

    ```
    select * from customers right outer join seller on customers.seller_id = seller.id;
    +------+----------+--------+---------+-------------+-----------+----+------+
    | id   | name     | gender | address | contact     | seller_id | id | name |
    +------+----------+--------+---------+-------------+-----------+----+------+
    |    5 | YZQ      | 1      | ZJ      | 18112345678 |         1 |  1 | Pony |
    |    6 | chiclaim | 1      | CH      | 18312345678 |         1 |  1 | Pony |
    |    7 | Johnny   | 1      | CH      | 17312345678 |         1 |  1 | Pony |
    | NULL | NULL     | NULL   | NULL    | NULL        |      NULL |  2 | Jack |
    +------+----------+--------+---------+-------------+-----------+----+------+
    
    // 说明有的销售员还没有客户
    ```


### where 子句和条件查询


#### where子句设置条件的几个常见方法

- 比较运算，如大于、等于、不等于

    ```
    select * from customers where id>6;
    ```
- 判断范围

    ```
    // between ... and ...
    select * from customers where id between 6 and 7;
    // in
    select * from customers where id in(6,7);
    ```
- 判定空值

    ```
    // is null 或 is not null
    select * from customers where seller_id is null;
    ```
- 子查询

    ```
    select studentNo,studentName from tb_student where studentNo in (select studentNo from tb_score where score>80);
    ```

### group by 子句

```
// 表的所有数据
select * from customers;
+----+----------+--------+----------+-------------+-----------+
| id | name     | gender | address  | contact     | seller_id |
+----+----------+--------+----------+-------------+-----------+
|  5 | YZQ      | 1      | JiangSu  | 18112345678 |         1 |
|  6 | chiclaim | 1      | JiangSu  | 18312345678 |         1 |
|  7 | Johnny   | 1      | ZheJiang | 17312345678 |         1 |
|  8 | ZhangSan | 0      | ZheJiang | 18287654321 |      NULL |
|  9 | Lucy     | 0      | XinJiang | 13123456789 |      NULL |
+----+----------+--------+----------+-------------+-----------+

// 以 address 分组（address 相同的为一组）
// address=JiangSu 总共有2条记录
// address=ZheJiang 总共有2条记录
select address ,count(*) from customers group by address;
+----------+----------+
| address  | count(*) |
+----------+----------+
| JiangSu  |        2 |
| ZheJiang |        2 |
| XinJiang |        1 |
+----------+----------+

// 还可以多列来分组
// address 和 gender 一样的行分为一组
// 地址在Jiangsu，性别为1 的客户有2个
select address,gender,count(*) from customers group by address,gender;
+----------+--------+----------+
| address  | gender | count(*) |
+----------+--------+----------+
| JiangSu  | 1      |        2 |
| ZheJiang | 1      |        1 |
| ZheJiang | 0      |        1 |
| XinJiang | 0      |        1 |
+----------+--------+----------+
```

### having 子句

在 select 语句中，除了可以使用 group by 子句分组数据外，还可以使用 having 子句来过滤分组

```
select address,gender,count(*) from customers group by address,gender having count(*)>=2;
+---------+--------+----------+
| address | gender | count(*) |
+---------+--------+----------+
| JiangSu | 1      |        2 |
+---------+--------+----------+
```

having 和 where 子句非常相似，但两者仍然存在以下几点：
- where子句主要用于过滤数据行，having子句主要用于过滤分组。
- having子句可以包含聚合函数，where子句则不可以。
- where子句会在分组前过滤，having子句则会在数据分组后进行过滤。因而where子句排除的行不会在分组中。

### order by 子句


在 select 语句中，可以使用 order by 子句将结果集中的数据行按一定的顺序进行排列，否则结果集中的数据行顺序是不可预测的。

```
// 以 id 倒序排列
select * from customers order by id desc;
+----+----------+--------+----------+-------------+-----------+
| id | name     | gender | address  | contact     | seller_id |
+----+----------+--------+----------+-------------+-----------+
|  9 | Lucy     | 0      | XinJiang | 13123456789 |      NULL |
|  8 | ZhangSan | 0      | ZheJiang | 18287654321 |      NULL |
|  7 | Johnny   | 1      | ZheJiang | 17312345678 |         1 |
|  6 | chiclaim | 1      | JiangSu  | 18312345678 |         1 |
|  5 | YZQ      | 1      | JiangSu  | 18112345678 |         1 |
+----+----------+--------+----------+-------------+-----------+
```

order by 子句需要注意一下几点：
- order by 子句中可以包含子查询
- 当对空值进行排序时，order by 子句会将空值当做最小值来对待。
- 若 order by 子句中指定多个列进行排序，则在 mysql 中会按照这些列从左到右所罗列的次序依次排序。
- 在 使用 group by 子句同时，通常也会同时使用 order by 子句。

### limit 子句


可以使用 limit 子句来限制 select 语句返回的结果集行数。

语法：`limit {[offset,] row_count | row_count OFFSET offset}`

- offset 默认为 0
- row_count 用于指定返回的数据行数
- row_count OFFSET offset：从 offset+1 行开始，取 row_count 行

```
// 对上面子使用 limit
select * from customers order by id desc limit 1,2;
+----+----------+--------+----------+-------------+-----------+
| id | name     | gender | address  | contact     | seller_id |
+----+----------+--------+----------+-------------+-----------+
|  8 | ZhangSan | 0      | ZheJiang | 18287654321 |      NULL |
|  7 | Johnny   | 1      | ZheJiang | 17312345678 |         1 |
+----+----------+--------+----------+-------------+-----------+

```

## 视图

从数据库的三级模式中可以看到模式（对应到基本表）是数据库中全体数据的逻辑结构，当不同的用户需要基本表中不同的数据，可以为这些不同的用户建立不同的`外模式`。

外模式中的内容来自模式，它是模式的部分数据或重构的数据。外模式对应到数据库中的概念就是试图（View）

### 创建视图

```
create view view_customers as select * from customers where gender = '1' with check option;

```

`with check option` 用于指定在可更新视图上所进行的修改都需要符合 select_statement 中所指定的限制条件。

### 删除视图

```
drop view view_name;
```

### 修改视图定义

```
// 类似创建视图
alter view view_customer as select * from customers with check option;

```

### 查看视图定义

```
show create view view_name;
```

### 更新视图数据

#### 通过 insert 语句

```
insert into view_customers values(10,'Lisi','1','Jiangxi','18345678901',2);

```
需要注意的是，插入的值的个数必须和视图的列一样，主键、默认值也需要手动输入

上面定义视图的时候，where 条件为 gender = '1'，如果添加的数据 gender = '0', 则会报错：

```
insert into view_customers values(11,'Lisi','0','Jiangxi','18345678901',2);
ERROR 1369 (HY000): CHECK OPTION failed 'mysql_test.view_customers'
```
另外，如果视图依赖多个表，则不能向该视图插入数据，因为mysql 不知道更新哪个表

#### 通过 update 语句

```
// 仍然只会影响 gender=1 的记录
update view_customers set seller_id = 1;
```
如果视图依赖多个表，则一次视图修改只能修改一个基本表中的数据

#### 通过 delete 语句
```
// 仍然只会影响 gender=1 的记录
delete from  view_customers where id >8;
```

对于依赖多个表的视图，不能使用 delete 语句

#### 查询视图

查询视图和查询表语法非常类型，将视图名代替表名即可。



## 存储过程

存储过程是一组为了完成某项特定功能的 SQL 语句集。

其实质就是一段处处在数据库中的代码，它可以由声明式（create、update 和select 语句）的 SQL 语句和过程式（if...then...else控制解构语句） SQL 语句组成。

这组语句集经过编译后会存储在数据库中，用户只需要通过制定存储过程的名字并给定参数，即可随时调用并执行他们，而不必重新编译，因此这种通过定义一段程序存储在数据库中的方式，可加大数据库操作语句的执行效率。

存储过程通常具有以下一些好处：

- 增加 SQL 语言的功能和灵活性
- 良好的封装
- 高性能
- 可减少网络流量
- 存储过程可作为一种安全机制来确保数据库安全性和数据完整性



### 创建存储过程

```
delimiter $$
create procedure pro_customers(in p_id int ,in p_gender char(1))
begin
    update customers set gender = p_gender where id = p_id;
end $$
```

解析：

- delimiter 用来设置结束标志。mysql 默认结束标志位`;`号，由于存储过程里可能存在多条 SQL 语句，那么就会存在多个分号，为了能够完整地执行存储过程，需要这只一个与分号不同的结束符。
- create procedure 后面是存储过程名称，括号里面是参数，参数前面可以是 in（输入参数）、out（输出参数）、inout（输入输出参数） 
- begin 和 end 之间是存储过程体，end 后面是结束标志，表示整个存储过程结束了。

存储过程体不仅可以添加 SQL 语句，还可以在里面声明局部变量，逻辑判断等。

### 存储过程体

- 声明局部变量
```
declare local_name type

declare p_name char(20);
```
- set 语句

```
//为变量赋值
set local_name = 'yuzhiqiang'
```
- select ... into 语句

可以通过 select  into 语句将查询的结果设置给变量

```
select name into local_name from customers where id =9;
```

- 流程控制语句

```
// 类似高级设计语言
if ... then ... else ... 语句

case 语句

// 循环语句
while、repeat、loop
```

- 游标

```
// 声明游标
declare cursor_name CURSOR FOR select_statement;

// 打开游标
open cursor_name

//读取数据
fetch cursor_name into var_name [,var_name]...

//关闭游标
close cursor_name

```

一个综合的案例：

```
delimiter $$

create procedure pro_customer_count(in p_gender char(1),out row_count int)

begin

    // 声明变量接受查询的结果值
    declare cid int;
    
    // 声明布尔值变量，用于控制循环
    declare flag boolean default true;
    
    // 声明游标
    declare cursor_query cursor for 
        select id from customers where gender = p_gender;
    
    // 声明句柄，当条件出现时会执行后面代码
    // 查询时没有数据返回时会触发
    declare continue handler for not found 
        set flag = false;
    
    // 将行数初始为0
    set row_count = 0;
    
    // 打开游标
    open cursor_query;
    // 提取数据
    fetch cursor_query into cid;
    // while ... do 循环
    while flag do
        set row_count = row_count+1;
        fetch cursor_query into cid;
    end while;

end$$

```

### 调用存储过程

```
已上面为例：
// 有入参和出参
call pro_customer_count(1, @rows);
// 查询出参结果
select @rows;

```

### 删除存储过程

```
drop procedure procedure_name;
```

## 存储函数

存储函数和存储过程一样，都是由 SQL 语句和过程式语句组成的代码片段，并且可以被应用程序和其他 SQL 语句调用。然而，他们主要由如下几点区别：

- 存储函数不能有输出参数，存储函数自身就是输出参数；存储过程可以有输出参数。
- 可以直接对存储函数进行调用，不需要使用 CALL 语句；存储过程的调用需要使用 CALL 语句。

### 创建存储函数：

```

DELIMITER $$
CREATE FUNCTION fn_getSexById(cid INT) RETURNS char(5) DETERMINISTIC

BEGIN

    DECLARE SEX CHAR(2);
    
    SELECT gender INTO SEX FROM customers where id = cid;
    
    IF SEX IS NULL THEN RETURN (SELECT '没有该客户');
    ELSEIF SEX = '0' THEN RETURN (SELECT '女');
    ELSE RETURN (SELECT '男');
    END IF;
    
END $$
```

DETERMINISTIC 用于指定存储函数的特性，除了指定 `DETERMINISTIC`，还是指定为 `NO SQL` 或 `READS SQL DAT`

- DETERMINISTIC：指明存储函数的执行结果是确定的。
- NO SQL：表示子程序中不包含SQL语句；
- READS SQL DATA：表示子程序中包含读数据的语句；注意：如果开启了bin-log,就必须为存储函数指定相应的特性；

                
### 调用存储函数

```
SELECT fn_getSexById(1)
```

### 删除存储函数

```
DROP FUNCTION fn_getSexById
```
