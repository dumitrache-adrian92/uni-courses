-- query with two columns: city and number of donors that can donate to acceptors in the same city with the same blood type and enough blood
-- oracle sql with tables DONOR and acceptors
-- table DONOR has columns did, city, bg, and amount
-- table acceptors has columns aid, city, bg, and amount

select d.city, count(*) as num_donors
from donor d, acceptor a
where d.city = a.city and d.bg = a.bg and d.amount >= a.amount
group by d.city
order by d.city;
