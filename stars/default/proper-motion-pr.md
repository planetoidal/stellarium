
### Store correct proper motion values in star catalog files

The Stellarium catalog files that store proper-motion data (`stars_0_ovo_8.cat`, `stars_1_0v0_8.cat`, `stars_2_0_v0_8.cat`) 
currently contain incorrect proper-motion values.  This pull request provides modified code that
calculates the correct proper-motion values for these catalog files.

### Background

The 2018 paper “Comparison of astronomical software programs
for archaeoastronomical applications”, by De Lorenzis, A. and V. Orofino (full citation given in the
bibliography of the Stellarium User Guide) compares how different astronomical programs
compute stellar positions at  times ranging from 2,500 BC to 10,000 BC.  

This paper (which I will abbreviate as DL&O) 
points out that Stellarium exhibits significant inaccuracies when computing the positions of stars with
high proper motions.  The paper suggests that these inaccuracies are due to the fact that Stellarium
ignores the observed radial velocities of stars when calculating their positions over time, and only uses the
proper motion (motion observed in right acension and declination).

It is true that ignoring the radial velocity will lead to increasing inaccuracies over time, but I was able to determine
that **a more significant problem is that the proper-motion values in the Stellarium star catalogs are incorrect**!

The inaccuracies in the catalog are not obvious, because the catalog does not contain the raw proper motion data
(changes in RA and declination in milli-arc-seconds per year).  Instead, the values stored in the catalog are derived
values, designed to be used efficiently in the Stellarium software.  Unfortunately, the way the values in the
catalog are calculated is inconsistent with how the values are used in Stellarium.

I have been able to fix this problem by correcting the values in the catalog files.

### Comparison

I will show some tables for comparison, but first a few words about how the comparision
was generated.

The DL&O paper used a program named Orion, written 
by Patrick
Wallace of STFC Rutherford Appleton Laboratory, UK, as the source for correct stellar positions over time.

I do not have access to this program.  However, DL&O provides the declination values (but not the RAs) calculated
by Orion,
for selected stars at selected times, and they provide the corresponding declination errors in Stellarium.

<!--
(Ignore...)
However, the paper notes that the Cartes du Ciel program produces
hightly accurate positional values in the time frame of interest.  So I downloaded this program and
had it calculate a series of positions, using the same stars and the same dates as De Lorenzis and Orofino.
(It should be noted that in the Cartes du Ciel [source code on github](https://github.com/pchev/skychart), 
the ProperMotion procedure
has the comment, "communicated by Patrick Wallace, RAL Space, UK".)
-->

DL&O ran their comparisons on 25 bright and/or significant stars, on 5 different dates in the past.
For the table below, I used the seven stars that DL&O reported as showing significant errors in Stellarium
at the most recent date (2,500 BC).
As a point of comparision, I added Rigel, a low-proper-motion star where Stellairum did not show significant errors, 
even at the most ancient date (10,000 BC).

In the table below, the column labeled **DL&O** contains a copy of the Stellarium
declination errors (∆δ, in degrees)
that are presented in Tables 2, 3, and 4 of DL&O.  

The **Cur** column gives
the declination errors when I use the current version of Stellarium (0.21.2).  If my calculations match those
of DL&O, the values in the **DL&O** and **Cur** columns should be identical.  In fact, they are very close, with a
maximum difference of 0.02 degrees.

The **New** column shows the declination errors when the current version of Stellarium is used in conjunction with
my recalculated star catalogs.  To be clear, the Stellarium software is unchanged; only the `dx0` and `dx1` values in
the star catalogs are different.  

Numbers are printed in **bold** if they are 0.08 or above, and in italics if they are between 0.05 and 0.08.  These 
correspond to criteria mentioned in DL&O. 


<table>
  <tr>
    <th>Star</th>
    <th>Year</th>
    <th>DL&O</th>
    <th>Cur</th>
    <th>New</th>
  </tr>
  <tr><td colspan="5"></td></tr>
  <tr>
    <td rowspan="5">Acrux</td>
    <td>2500 BC</td>
    <td><i>0.06</i></td>
    <td><i>0.06</i></td>
    <td>-0.00</td>
  </tr>
  <tr>
    <td>4500 BC</td>
    <td><i>0.08</i></td>
    <td><b>0.09</b></td>
    <td>-0.00</td>
  </tr>
  <tr>
    <td>6000 BC</td>
    <td><b>0.10</b></td>
    <td><b>0.10</b></td>
    <td>-0.00</td>
  </tr>
  <tr>
    <td>8000 BC</td>
    <td><b>0.11</b></td>
    <td><b>0.11</b></td>
    <td>-0.01</td>
  </tr>
  <tr>
    <td>10000 BC</td>
    <td><b>0.10</b></td>
    <td><b>0.11</b></td>
    <td>-0.01</td>
  </tr>
  <tr><td colspan="5"></td></tr>
  <tr>
    <td rowspan="5">Arcturus</td>
    <td>2500 BC</td>
    <td><b>-0.32</b></td>
    <td><b>-0.31</b></td>
    <td>-0.04</td>
  </tr>
  <tr>
    <td>4500 BC</td>
    <td><b>-0.46</b></td>
    <td><b>-0.45</b></td>
    <td><b>-0.10</b></td>
  </tr>
  <tr>
    <td>6000 BC</td>
    <td><b>-0.52</b></td>
    <td><b>-0.52</b></td>
    <td><b>-0.17</b></td>
  </tr>
  <tr>
    <td>8000 BC</td>
    <td><b>-0.48</b></td>
    <td><b>-0.49</b></td>
    <td><b>-0.28</b></td>
  </tr>
  <tr>
    <td>10000 BC</td>
    <td><b>-0.45</b></td>
    <td><b>-0.46</b></td>
    <td><b>-0.38</b></td>
  </tr>
  <tr><td colspan="5"></td></tr>
  <tr>
    <td rowspan="5">Dubhe</td>
    <td>2500 BC</td>
    <td><b>0.15</b></td>
    <td><b>0.15</b></td>
    <td>-0.01</td>
  </tr>
  <tr>
    <td>4500 BC</td>
    <td><b>0.15</b></td>
    <td><b>0.14</b></td>
    <td>-0.02</td>
  </tr>
  <tr>
    <td>6000 BC</td>
    <td><b>0.18</b></td>
    <td><b>0.17</b></td>
    <td>-0.02</td>
  </tr>
  <tr>
    <td>8000 BC</td>
    <td><b>0.25</b></td>
    <td><b>0.24</b></td>
    <td>-0.02</td>
  </tr>
  <tr>
    <td>10000 BC</td>
    <td><b>0.38</b></td>
    <td><b>0.37</b></td>
    <td>-0.02</td>
  </tr>
  <tr><td colspan="5"></td></tr>
  <tr>
    <td rowspan="5">Rigel</td>
    <td>2500 BC</td>
    <td>0.00</td>
    <td>-0.00</td>
    <td>-0.00</td>
  </tr>
  <tr>
    <td>4500 BC</td>
    <td>0.00</td>
    <td>-0.00</td>
    <td>-0.00</td>
  </tr>
  <tr>
    <td>6000 BC</td>
    <td>0.00</td>
    <td>-0.01</td>
    <td>-0.01</td>
  </tr>
  <tr>
    <td>8000 BC</td>
    <td>0.00</td>
    <td>-0.00</td>
    <td>-0.00</td>
  </tr>
  <tr>
    <td>10000 BC</td>
    <td>0.01</td>
    <td>0.01</td>
    <td>0.01</td>
  </tr>
  <tr><td colspan="5"></td></tr>
  <tr>
    <td rowspan="5">Sirius</td>
    <td>2500 BC</td>
    <td><b>-0.13</b></td>
    <td><b>-0.14</b></td>
    <td>-0.04</td>
  </tr>
  <tr>
    <td>4500 BC</td>
    <td><b>-0.23</b></td>
    <td><b>-0.23</b></td>
    <td><i>-0.07</i></td>
  </tr>
  <tr>
    <td>6000 BC</td>
    <td><b>-0.30</b></td>
    <td><b>-0.31</b></td>
    <td><b>-0.11</b></td>
  </tr>
  <tr>
    <td>8000 BC</td>
    <td><b>-0.42</b></td>
    <td><b>-0.42</b></td>
    <td><b>-0.17</b></td>
  </tr>
  <tr>
    <td>10000 BC</td>
    <td><b>-0.52</b></td>
    <td><b>-0.52</b></td>
    <td><b>-0.24</b></td>
  </tr>
  <tr><td colspan="5"></td></tr>
  <tr>
    <td rowspan="5">Thuban</td>
    <td>2500 BC</td>
    <td><i>-0.07</i></td>
    <td>-0.05</td>
    <td>0.01</td>
  </tr>
  <tr>
    <td>4500 BC</td>
    <td><i>0.08</i></td>
    <td><i>0.07</i></td>
    <td>-0.01</td>
  </tr>
  <tr>
    <td>6000 BC</td>
    <td><b>0.09</b></td>
    <td><i>0.08</i></td>
    <td>-0.01</td>
  </tr>
  <tr>
    <td>8000 BC</td>
    <td><i>0.08</i></td>
    <td><i>0.07</i></td>
    <td>-0.02</td>
  </tr>
  <tr>
    <td>10000 BC</td>
    <td><i>0.06</i></td>
    <td>0.05</td>
    <td>-0.01</td>
  </tr>
  <tr><td colspan="5"></td></tr>
  <tr>
    <td rowspan="5">Toliman</td>
    <td>2500 BC</td>
    <td><b>3.48</b></td>
    <td><b>3.47</b></td>
    <td><i>0.07</i></td>
  </tr>
  <tr>
    <td>4500 BC</td>
    <td><b>5.32</b></td>
    <td><b>5.30</b></td>
    <td>0.04</td>
  </tr>
  <tr>
    <td>6000 BC</td>
    <td><b>6.68</b></td>
    <td><b>6.66</b></td>
    <td><b>-0.11</b></td>
  </tr>
  <tr>
    <td>8000 BC</td>
    <td><b>8.19</b></td>
    <td><b>8.17</b></td>
    <td><b>-0.55</b></td>
  </tr>
  <tr>
    <td>10000 BC</td>
    <td><b>8.97</b></td>
    <td><b>8.96</b></td>
    <td><b>-1.32</b></td>
  </tr>
  <tr><td colspan="5"></td></tr>
  <tr>
    <td rowspan="5">Vega</td>
    <td>2500 BC</td>
    <td><b>0.13</b></td>
    <td><b>0.14</b></td>
    <td>0.01</td>
  </tr>
  <tr>
    <td>4500 BC</td>
    <td><b>0.21</b></td>
    <td><b>0.22</b></td>
    <td>0.01</td>
  </tr>
  <tr>
    <td>6000 BC</td>
    <td><b>0.27</b></td>
    <td><b>0.28</b></td>
    <td>0.01</td>
  </tr>
  <tr>
    <td>8000 BC</td>
    <td><b>0.34</b></td>
    <td><b>0.35</b></td>
    <td>0.02</td>
  </tr>
  <tr>
    <td>10000 BC</td>
    <td><b>0.40</b></td>
    <td><b>0.41</b></td>
    <td>0.01</td>
  </tr>
</table>

The results in the **New** column show that the errors for four of the stars (Acrux, Dubhe, Thuban, and Vega)
have been reduced to insignificance, even as far back as 10,000 BC.
The errors for Arcturus, Sirius, and Toliman have
been reduced (significantly, in the case of Toliman) but are still unacceptable at
10,000 BC, according to DL&O's criteria.
Of course, Rigel, the low-proper-motion star, shows insignificant errors in both the **Cur** and **New**
columns.

### `dx0` and `dx1` in Stellarium

In this section I will show how Stellarium uses the `dx0` and dx1` values that are provided by the star
catalog.  In the next section, I will show derive the formulas for calculating these values, given
the proper motions in RA and declination.

The key code is in `src/code/modules/Star.hpp`:
```
	void getJ2000Pos(const ZoneData *z,float movementFactor, Vec3f& pos) const
	{
		pos = z->axis0;
		pos*=(static_cast<float>(getX0())+movementFactor*getDx0());
		pos+=(static_cast<float>(getX1())+movementFactor*getDx1())*z->axis1;
		pos+=z->center;
	}
```
