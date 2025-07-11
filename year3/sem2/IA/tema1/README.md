# Course schedule generator

Anyone who's been to a relatively packed university has probably complained
about their horrible schedule, but even those tiring schedules probably took
ages to make. Creating a high quality timetable to serve university students
is a very difficult problem due to the high amount of possibilities and
restrictions.

Here is a course timetable generator based on a Hill Climbing style
algorithm (and a less successful Monte Carlo Tree Search approach) that
attempts to find an adequate solution taking into account physical restrictions
such as professors not being able to teach two courses simultaneously, as well
as more human/subjective restrictions such as a professor not wanting to teach
on mondays.

While the results are fairly decent, usualy being able to generate a correct
schedule that allocates all the students who need to take a course while
respecting all restrictions, it's not perfect. Currently it doesn't take into
consideration that professors might not want to have gaps between courses on
the same day or the needs of students (which might also have similar wishes).
Real life scenarios also have quite a few more restrictions and can have way
more complicated systems (e.g: my uni has courses that have 3 hour lectures,
courses that have 2 hour lecture with one weekly and the other bi weekly etc.).
