
### Store correct proper motion values in star catalog files

The Stellarium catalog files that store proper-motion data (`stars_0_ovo_8.cat`, `stars_1_0v0_8.cat`, `stars_2_0_v0_8.cat`) 
currently contain incorrect proper-motion values.  This pull request provides modified code that
calculates the correct proper-motion values for these catalog files.

### Background

The 2018 paper “Comparison of astronomical software programs
for archaeoastronomical applications”, by De Lorenzis, A. and V. Orofino (full citation given in the
bibliography of the Stellarium User Guide) compares how different astronomical programs
compute stellar positions in time scales of interest to archeologists, for instance back to
10,000 BC.  

This paper notes that Stellarium has significant innacuracies when computing the positions of stars with
high proper motions.  The paper suggests that these inaccuracies are due to the fact that Stellarium
ignores the observed radial velocities of stars when calculating their positions over time, and only uses the
"proper motion" (motion observed in right acension and declination).

It is true that ignoring the radial velocity will lead to increasing inaccuracies over time, but I determined
that the proper-motion information in the Stellarium star catalogs is calculated in a way that is inconsistent with how that
information is used when the catalog is read into the program.  In other words, Stellarium's accuracy problems
with high-proper-motion stars are mostly due to the fact that the proper-motion values in the catalog are incorrect!

I was able to fix this problem.  

### Comparison

I will show some tables for comparison, but first a few words about how the comparision
was generated.

The De Lorenzis and Orofino paper used a program named Orion, written 
by Patrick
Wallace of STFC Rutherford Appleton Laboratory, UK, as the source for correct stellar positions.

I do not have access to this program.  However, the paper notes that the Cartes du Ciel program produces
hightly accurate positional values in the time frame of interest.  So I downloaded this program and
had it calculate a series of positions, using the same stars and the same dates as De Lorenzis and Orofino.
(It should be noted that in the Cartes du Ciel [source code on github](https://github.com/pchev/skychart), 
the ProperMotion procedure
has the comment, "communicated by Patrick Wallace, RAL Space, UK".)


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
