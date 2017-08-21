
<!-- README.md is generated from README.Rmd. Please edit that file -->
Transforming Excel well raw data into datasets
==============================================

5.1 Data Introspection
----------------------

This section is about getting familiar with our data. We will be using functions to know the size of our table or data frame, the names of the columns or variables, the staructure of the data and the type of data for each of the variables or colummns.

### Read the raw data again

``` r
# load the library xlsx
library(xlsx)
#> Loading required package: rJava
#> Loading required package: xlsxjars

# read the raw data
myXl <- read.xlsx("../extdata/oilfield_100w_raw_data.xlsx", 
                  sheetIndex = 1, stringsAsFactors = FALSE)
```

### Printing the head

Let's print 6 rows of data with the function head(). You will see a long printing. We will fix this in a minute. Read on.

``` r
# the function head() prints the first 6 rows
# to print the last 6 rows use tail()
print(head(myXl))
#>        Wellname       Company Analyst Field Location Platform Fluid
#> 1  PSCO-M005-TS Oil Gains Co.    Aida PISCO  M005-TS        M     0
#> 2 PSCO-M0007-TS Oil Gains Co.    Aida PISCO  M007-TS        M     0
#> 3  PSCO-M004-LS Oil Gains Co.    Aida PISCO  M004-LS        M     0
#> 4  PSCO-M008-TS Oil Gains Co.    Aida PISCO  M008-TS        M     0
#> 5  PSCO-M010-SS Oil Gains Co.    Aida PISCO  M010-SS        M     0
#> 6  PSCO-M006-TS Oil Gains Co.    Aida PISCO  M006-TS        M     0
#>   WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 1        0         1          0           0       27   445.7    36.0
#> 2        0         1          0           0       22   473.0    36.0
#> 3        0         1          0           0       11   280.0    36.0
#> 4        0         1          0           0       14   414.0    36.0
#> 5        0         1          0           0       13   420.0    35.2
#> 6        0         0          0           0       20   416.0    36.0
#>   PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 1        1.2             25000       0    65.5           3             2
#> 2        1.2             25000       0    65.0           3             2
#> 3        1.2             25000       0    65.0           3             2
#> 4        1.2             25000       0    65.0           3             2
#> 5        1.2             25000       0    65.0           3             2
#> 6        1.2             25000       0    65.0           3             2
#>   PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 1        209       1821       10        0         930         209
#> 2        209       1921       10        0        1300         209
#> 3        209       1753        1        1        1573         209
#> 4        209       1698       10        1        1286         200
#> 5        209       1722       10        0        1468         209
#> 6        209       1753       10        0        1286         209
#>   IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES IPR_PI   GEO_THMD GEO_THTEMP
#> 1     1449.0     66       384.0       331.000   4.56  0|2289.5|    90|209|
#> 2     1581.5     70       973.7       956.000   1.15    0|1744|    90|200|
#> 3     1235.0      0      1327.0       941.436   0.71 0|1954.09|    80|200|
#> 4     4867.0      5       150.8       418.464   0.25    0|1720|    90|200|
#> 5      420.0     90      1290.3       430.877   1.35    0|2308|    90|200|
#> 6     6000.0     80       559.0       902.000   7.80 0|1496.87|    90|200|
#>   GL_method                                  GL_ArrayMandrels GL_Vdepth
#> 1         0                              0|0|0|0|0|0|0|0|0|0|   1807.53
#> 2         0             614.3|1118|1422.5|1564.6|0|0|0|0|0|0|   1564.60
#> 3         2        167.152|245.913|327.69|373.99|0|0|0|0|0|0|   1227.00
#> 4         2           560.9|1123.8|1427.6|1569.6|0|0|0|0|0|0|      0.00
#> 5         0 193.054|380.384|487.893|584.93|649.657|0|0|0|0|0|   1911.98
#> 6         2              543.1|969.3|1235.2|1358|0|0|0|0|0|0|    969.30
#>   GL_GSG GL_CO2
#> 1    1.2     65
#> 2    1.2     65
#> 3    1.2     65
#> 4    1.2     65
#> 5    1.2     65
#> 6    1.2     65
#>                                                                                                                                                                                                                                                                                                     WT_DATE
#> 1 09/09/2014|02/07/2012|08/08/2012|02/09/2012|03/10/2012|11/11/2012|08/12/2012|13/12/2012|02/01/2013|18/01/2013|03/02/2013|04/03/2013|14/04/2013|21/06/2013|23/07/2013|03/08/2013|22/09/2013|07/10/2013|08/11/2013|08/11/2013|25/01/2014|06/02/2014|09/03/2014|10/06/2014|05/07/2014|06/08/2014|09/09/2014|
#> 2                                                        09/06/2014|21/08/2014|06/02/2012|17/03/2012|11/07/2012|10/08/2012|03/09/2012|05/10/2012|18/11/2012|22/01/2013|11/03/2013|10/04/2013|18/06/2013|04/07/2013|30/07/2013|23/09/2013|14/10/2013|10/11/2013|18/04/2014|21/07/2014|21/08/2014|06/09/2014|
#> 3                                                                                                                                                                                 12/02/2004|04/04/2000|04/05/2000|25/07/2000|01/01/2001|03/02/2001|22/02/2001|02/04/2001|01/06/2001|27/11/2003|12/02/2004|
#> 4                                                                                                                                                17/02/2014|02/04/2009|22/05/2009|13/06/2009|03/07/2009|01/08/2009|05/09/2009|19/10/2009|23/10/2009|06/11/2009|01/12/2009|13/12/2009|12/07/2011|17/02/2012|
#> 5                                                                                                                                                           06/09/2009|21/09/2009|05/10/2009|02/11/2009|02/12/2009|16/01/2010|07/03/2010|11/07/2008|15/07/2008|24/07/2008|31/07/2008|07/09/2008|03/10/2008|
#> 6                                                                              09/07/2012|10/08/2012|17/09/2012|11/10/2012|11/11/2012|16/01/2013|03/03/2013|15/04/2013|18/06/2013|05/07/2013|03/08/2013|21/09/2013|13/10/2013|23/11/2013|23/11/2013|16/04/2014|19/06/2014|18/08/2014|04/09/2014|09/10/2014|
#>                                                                                                         WT_THT
#> 1 121|112|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|
#> 2                     125|125|125|125|135|125|125|127|125|125|125|125|125|125|125|125|125|125|125|125|125|122|
#> 3                                                                           96|99|99|99|99|99|99|99|99|124|99|
#> 4                                                     108|108|108|108|108|108|108|108|108|108|108|108|108|108|
#> 5                                                         190|192|190|190|190|188|145|190|190|190|190|190|192|
#> 6                             125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|152|125|125|125|
#>                                                                                                                                                             WT_LIQRT
#> 1 561.2|384.5|365.8|405.3|312.2|501.1|469.9|551.1|887.2|534.7|474.2|408.7|527.2|266.9|377.8|540.6|462.5|540.2|540.9|541.1|546.8|559.2|559.2|561.1|559.6|559.3|561.2|
#> 2                                   560|528|711.2|790.6|973.7|732.4|402.5|747.8|793.5|958.9|1190.5|1135.3|909.1|1006.4|980|1013.9|550.6|551.7|591.3|528.3|528.3|560|
#> 3                                                                                                        382.6|1296|862|739.6|486|1247|208.6|505.8|345.1|1327|382.6|
#> 4                                                                                   150.8|93.9|257.8|213.5|255.1|246.9|218.2|48.4|56.6|96.7|281.2|109.8|127.9|150.8|
#> 5                                                                           1369.3|1244.9|1035.3|1049.9|1104.3|961.7|1290.3|1911.8|1187.8|2578.1|2369|1831.3|1544.3|
#> 6                                       1108.8|1440.4|1400.6|543.5|1417.3|676.6|1228.9|479.7|1050.2|1431.1|528|1399.7|553.5|555|555.3|1448|1344.6|557.4|559.7|558.9|
#>                                                                                                                                                WT_WC
#> 1 65|66.9|71.08|71.09|75.96|71.1|71.09|68.66|71.1|63.42|71.09|71.08|71.08|26.04|71.09|71.09|71.08|31.1|31.06|31.13|51.31|28.09|28.09|50|50|50|65.03|
#> 2                         70|68|65.94|80.83|75.97|74.75|75.96|75.97|73.09|77.8|76.95|76.94|61.26|75.97|71.09|71.09|71.11|71.1|67.31|68.5|68.5|70.01|
#> 3                                                                                                            0|0|0.01|0|0.05|0|3.02|27.98|17.06|0|0|
#> 4                                                                                                      5|0|20.36|0|0|0|3.46|0|0|0|9.26|0|15.94|5.01|
#> 5                                                                        95.13|92|90.46|90.46|92.83|90.46|95.19|71.14|88.69|60.59|75.74|90.46|90.46|
#> 6                              80.64|71.09|85.66|80.83|99.85|90.46|97.66|85.66|80.82|95.24|84.89|90.46|80.84|80.83|80.86|80|80.01|79.89|79.97|80.01|
#>                                                                                                                                               WT_THP
#> 1 246.5|232.1|246.6|217.6|246.6|217.6|217.6|203|203|203|232.1|232.1|232.1|232.1|261.1|217.6|246.6|232.1|232|232.1|232.1|232|217.5|203|203|232|246.5|
#> 2                          246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 3                                                                                               435|304.5|348|348|334|334|304.5|334|304.5|290|435.1|
#> 4                                                               362.6|464.1|507.6|507.6|319.1|304.6|290.1|304.6|304.6|304.6|290.1|319.1|391.6|362.6|
#> 5                                                                     261.1|217.6|246.6|232.1|232.1|217.6|261.1|217.6|261.1|217.6|246.6|246.6|217.6|
#> 6                                 304.6|362.6|304.6|348.1|319.1|290.1|246.6|261.1|290.1|333.6|362.6|304.6|261.1|275.6|275.5|319|333.5|188.5|319|290|
#>                                                                                                                                            WT_GOR
#> 1        3145|1449|2108|2496|4214|4672|3689|3688|4216|542.6|426|4215|4214|460.4|4216|4216|4215|2243|1874|1166|1737|1468|1741|2352|2609|2599|3145|
#> 2 4160|3974|1624.7|336.5|1581.5|287.5|1581|1581.8|1053|1265.5|1265.9|1160.1|759.6|1160.2|1160.1|1632.6|2974.1|4081.5|1759.7|3974.1|3974.1|3831.9|
#> 3                                                                                       453|573.5|4186|2976|952.7|1848|1347|1227|1015|1235|453.1|
#> 4                                     4867|46172.6|17401.8|16889.5|13548.2|13622.8|16676.7|85862.6|66214.7|59297.7|12641.8|31426.3|5126.4|4867.5|
#> 5                                                                          869|1800|43.9|2963|415.4|1800|411.3|273.7|322.3|267.9|43.4|1870.4|450|
#> 6                1476.3|1371|1265.8|1266|1573.4|1686.4|1794.5|1792.9|600.5|1792|1792.3|3188.6|5614.4|6910.6|6990.9|967.8|2789|5802|6528.4|6727.8|
#>                                                                                                    WT_GLIR
#> 1 0|0|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|
#> 2              0.5|0.6|0.1|0.1|0.25|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.265|
#> 3                                                             0.2|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|
#> 4                                                   0|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|
#> 5                                                     0.3|0.5|0.3|0.3|0.3|0.1|0.4|0.2|0.2|0.3|0.2|0.1|0.1|
#> 6                                                                 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#>                                                                                                                                                                                                                   WT_DEPTH
#> 1 1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|
#> 2                                                               1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|
#> 3                                                                                                                                                                  1227|1227|1227|1227|1227|1227|1227|1227|1227|1227|1227|
#> 4                                                                                                                       1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|
#> 5                                                                                                                             2142.8|2142.8|2142.8|2142.8|2142.8|2142.8|1911.98|2142.8|2142.8|2142.8|2142.8|2142.8|2142.8|
#> 6                                                                                                                                                                                 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#>                                                WT_Enable
#> 1 0|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|
#> 2           1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 3                                 1|1|1|1|1|1|1|1|1|0|1|
#> 4                           1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 5                             1|1|1|1|1|1|0|1|1|1|1|1|1|
#> 6               1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|1|1|1|
#>                                                WT_GDEPTH
#> 1 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 2           0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 3                                 0|0|0|0|0|0|0|0|0|0|0|
#> 4                           0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 5                             0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 6               0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#>                                                                                                                                             WT_GPRES
#> 1 246.5|232.1|246.6|217.6|246.6|217.6|217.6|203|203|203|232.1|232.1|232.1|232.1|261.1|217.6|246.6|232.1|232|232.1|232.1|232|217.5|203|203|232|246.5|
#> 2                          246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 3                                                                                               435|304.5|348|348|334|334|304.5|334|304.5|290|435.1|
#> 4                                                               362.6|464.1|507.6|507.6|319.1|304.6|290.1|304.6|304.6|304.6|290.1|319.1|391.6|362.6|
#> 5                                                                     261.1|217.6|246.6|232.1|232.1|217.6|261.1|217.6|261.1|217.6|246.6|246.6|217.6|
#> 6                                 304.6|362.6|304.6|348.1|319.1|290.1|246.6|261.1|290.1|333.6|362.6|304.6|261.1|275.6|275.5|319|333.5|188.5|319|290|
#>                                                                                                       WT_RESPRES
#> 1   930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|
#> 2 1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|
#> 3                                                        1573|1573|1573|1573|1573|1573|1573|1573|1573|1573|1573|
#> 4                                         1286|1025|1025|1025|1025|1025|1025|1025|1025|1025|1025|1025|1025|1025|
#> 5                                               1468|900|1468|1468|1468|1468|1468|1468|1468|1468|1468|1468|1468|
#> 6           1286|1286|1286|1286|1286|1286|1286|1286|1286|1286|1286|1286|1286|1286|1286|1286|1275|1286|1286|1286|
#>                                      ProsperFilename
#> 1 \\\\network\\piscis\\well_models\\PISC-M005-TS.Out
#> 2 \\\\network\\piscis\\well_models\\PISC-M007-TS.Out
#> 3 \\\\network\\piscis\\well_models\\PISC-M004-LL.Out
#> 4 \\\\network\\piscis\\well_models\\PISC-M008-TS.Out
#> 5 \\\\network\\piscis\\well_models\\PISC-M010-SS.Out
#> 6 \\\\network\\piscis\\well_models\\PISC-M006-TS.Out
```

It looks pretty long. Let's try with a package that adds better printing capabilities: `tibble`.

Install `tibble`
----------------

Install it with `install.packages("tibble")`

``` r
library(tibble)      # load the package
myXl <- as_tibble(myXl)      # convert the data frame to a tibble
```

``` r
head(myXl)
#> # A tibble: 6 x 51
#>        Wellname       Company Analyst Field Location Platform Fluid
#>           <chr>         <chr>   <chr> <chr>    <chr>    <chr> <dbl>
#> 1  PSCO-M005-TS Oil Gains Co.    Aida PISCO  M005-TS        M     0
#> 2 PSCO-M0007-TS Oil Gains Co.    Aida PISCO  M007-TS        M     0
#> 3  PSCO-M004-LS Oil Gains Co.    Aida PISCO  M004-LS        M     0
#> 4  PSCO-M008-TS Oil Gains Co.    Aida PISCO  M008-TS        M     0
#> 5  PSCO-M010-SS Oil Gains Co.    Aida PISCO  M010-SS        M     0
#> 6  PSCO-M006-TS Oil Gains Co.    Aida PISCO  M006-TS        M     0
#> # ... with 44 more variables: WellType <dbl>, AL_Method <dbl>,
#> #   Completion <dbl>, SandControl <dbl>, WT_COUNT <dbl>, PVT_GOR <dbl>,
#> #   PVT_API <dbl>, PVT_SG_gas <dbl>, PVT_WaterSalinity <dbl>,
#> #   PVT_H2S <dbl>, PVT_CO2 <dbl>, PVT_PB_CORR <dbl>, PVT_VISC_CORR <dbl>,
#> #   PVT_BPTEMP <dbl>, PVT_BPPRES <dbl>, VLP_CORR <dbl>, IPR_CORR <dbl>,
#> #   IPR_RESPRES <dbl>, IPR_RESTEMP <dbl>, IPR_TOTGOR <dbl>, IPR_WC <dbl>,
#> #   IPR_VOGELRT <dbl>, IPR_VOGELPRES <dbl>, IPR_PI <dbl>, GEO_THMD <chr>,
#> #   GEO_THTEMP <chr>, GL_method <dbl>, GL_ArrayMandrels <chr>,
#> #   GL_Vdepth <dbl>, GL_GSG <dbl>, GL_CO2 <dbl>, WT_DATE <chr>,
#> #   WT_THT <chr>, WT_LIQRT <chr>, WT_WC <chr>, WT_THP <chr>, WT_GOR <chr>,
#> #   WT_GLIR <chr>, WT_DEPTH <chr>, WT_Enable <chr>, WT_GDEPTH <chr>,
#> #   WT_GPRES <chr>, WT_RESPRES <chr>, ProsperFilename <chr>
```

``` r
tail(myXl)
#> # A tibble: 6 x 51
#>        Wellname       Company  Analyst Field Location Platform Fluid
#>           <chr>         <chr>    <chr> <chr>    <chr>    <chr> <dbl>
#> 1  PSCO-S021-TS Oil Gains Co.   Camden PISCO  S021-TS        S     0
#> 2  PSCO-S016-SS Oil Gains Co.   Camden PISCO  S016-SS        S     0
#> 3  PSCO-S015-SS Oil Gains Co.   Camden PISCO  S015-SS        S     0
#> 4  PSCO-S012-LS Oil Gains Co.     <NA> PISCO  S012-LS        S     0
#> 5  PSCO-M001-TS Oil Gains Co.     Aida PISCO  M001-TS     <NA>     0
#> 6 PSCO-M0026-TS Oil Gains Co. Ibironke PISCO  M026-TS     <NA>     0
#> # ... with 44 more variables: WellType <dbl>, AL_Method <dbl>,
#> #   Completion <dbl>, SandControl <dbl>, WT_COUNT <dbl>, PVT_GOR <dbl>,
#> #   PVT_API <dbl>, PVT_SG_gas <dbl>, PVT_WaterSalinity <dbl>,
#> #   PVT_H2S <dbl>, PVT_CO2 <dbl>, PVT_PB_CORR <dbl>, PVT_VISC_CORR <dbl>,
#> #   PVT_BPTEMP <dbl>, PVT_BPPRES <dbl>, VLP_CORR <dbl>, IPR_CORR <dbl>,
#> #   IPR_RESPRES <dbl>, IPR_RESTEMP <dbl>, IPR_TOTGOR <dbl>, IPR_WC <dbl>,
#> #   IPR_VOGELRT <dbl>, IPR_VOGELPRES <dbl>, IPR_PI <dbl>, GEO_THMD <chr>,
#> #   GEO_THTEMP <chr>, GL_method <dbl>, GL_ArrayMandrels <chr>,
#> #   GL_Vdepth <dbl>, GL_GSG <dbl>, GL_CO2 <dbl>, WT_DATE <chr>,
#> #   WT_THT <chr>, WT_LIQRT <chr>, WT_WC <chr>, WT_THP <chr>, WT_GOR <chr>,
#> #   WT_GLIR <chr>, WT_DEPTH <chr>, WT_Enable <chr>, WT_GDEPTH <chr>,
#> #   WT_GPRES <chr>, WT_RESPRES <chr>, ProsperFilename <chr>
```

Now it looks much better.

### dimensions of the data frame: `dim`

Let's use some R functions to find out more about our data.

``` r
# get the dimensions of the table.
dim(myXl)
#> [1] 100  51
```

Our table has 100 rows and 51 columns.

### names of the columns: `names`

These are the names of the variables or columns:

``` r
names(myXl)
#>  [1] "Wellname"          "Company"           "Analyst"          
#>  [4] "Field"             "Location"          "Platform"         
#>  [7] "Fluid"             "WellType"          "AL_Method"        
#> [10] "Completion"        "SandControl"       "WT_COUNT"         
#> [13] "PVT_GOR"           "PVT_API"           "PVT_SG_gas"       
#> [16] "PVT_WaterSalinity" "PVT_H2S"           "PVT_CO2"          
#> [19] "PVT_PB_CORR"       "PVT_VISC_CORR"     "PVT_BPTEMP"       
#> [22] "PVT_BPPRES"        "VLP_CORR"          "IPR_CORR"         
#> [25] "IPR_RESPRES"       "IPR_RESTEMP"       "IPR_TOTGOR"       
#> [28] "IPR_WC"            "IPR_VOGELRT"       "IPR_VOGELPRES"    
#> [31] "IPR_PI"            "GEO_THMD"          "GEO_THTEMP"       
#> [34] "GL_method"         "GL_ArrayMandrels"  "GL_Vdepth"        
#> [37] "GL_GSG"            "GL_CO2"            "WT_DATE"          
#> [40] "WT_THT"            "WT_LIQRT"          "WT_WC"            
#> [43] "WT_THP"            "WT_GOR"            "WT_GLIR"          
#> [46] "WT_DEPTH"          "WT_Enable"         "WT_GDEPTH"        
#> [49] "WT_GPRES"          "WT_RESPRES"        "ProsperFilename"
```

### summary of the data: `summary`

``` r
# A summary of all the variables.
# Notice the difference between numerical and non-numerical variables
summary(myXl)
#>    Wellname           Company            Analyst         
#>  Length:100         Length:100         Length:100        
#>  Class :character   Class :character   Class :character  
#>  Mode  :character   Mode  :character   Mode  :character  
#>                                                          
#>                                                          
#>                                                          
#>                                                          
#>     Field             Location           Platform             Fluid  
#>  Length:100         Length:100         Length:100         Min.   :0  
#>  Class :character   Class :character   Class :character   1st Qu.:0  
#>  Mode  :character   Mode  :character   Mode  :character   Median :0  
#>                                                           Mean   :0  
#>                                                           3rd Qu.:0  
#>                                                           Max.   :0  
#>                                                                      
#>     WellType   AL_Method      Completion    SandControl      WT_COUNT    
#>  Min.   :0   Min.   :0.00   Min.   :0.00   Min.   :0.00   Min.   : 1.00  
#>  1st Qu.:0   1st Qu.:1.00   1st Qu.:0.00   1st Qu.:0.00   1st Qu.: 1.00  
#>  Median :0   Median :1.00   Median :0.00   Median :0.00   Median : 3.00  
#>  Mean   :0   Mean   :0.98   Mean   :0.07   Mean   :0.24   Mean   : 4.82  
#>  3rd Qu.:0   3rd Qu.:1.00   3rd Qu.:0.00   3rd Qu.:0.00   3rd Qu.: 7.00  
#>  Max.   :0   Max.   :1.00   Max.   :1.00   Max.   :3.00   Max.   :27.00  
#>                                                                          
#>     PVT_GOR         PVT_API        PVT_SG_gas    PVT_WaterSalinity
#>  Min.   :280.0   Min.   :35.00   Min.   :0.800   Min.   : 1000    
#>  1st Qu.:416.0   1st Qu.:36.00   1st Qu.:1.200   1st Qu.:15000    
#>  Median :423.0   Median :36.00   Median :1.200   Median :15000    
#>  Mean   :431.2   Mean   :36.15   Mean   :1.221   Mean   :15247    
#>  3rd Qu.:455.2   3rd Qu.:36.00   3rd Qu.:1.237   3rd Qu.:15125    
#>  Max.   :473.0   Max.   :46.15   Max.   :1.300   Max.   :30000    
#>                                                                   
#>     PVT_H2S     PVT_CO2       PVT_PB_CORR   PVT_VISC_CORR 
#>  Min.   :0   Min.   :29.00   Min.   :0.00   Min.   :0.00  
#>  1st Qu.:0   1st Qu.:65.00   1st Qu.:3.00   1st Qu.:1.00  
#>  Median :0   Median :65.00   Median :3.00   Median :2.00  
#>  Mean   :0   Mean   :66.58   Mean   :2.78   Mean   :1.77  
#>  3rd Qu.:0   3rd Qu.:69.25   3rd Qu.:3.00   3rd Qu.:2.00  
#>  Max.   :0   Max.   :74.28   Max.   :3.00   Max.   :4.00  
#>                                                           
#>    PVT_BPTEMP       PVT_BPPRES      VLP_CORR        IPR_CORR   
#>  Min.   : 97.78   Min.   :1683   Min.   : 0.00   Min.   :0.00  
#>  1st Qu.:208.00   1st Qu.:1722   1st Qu.:10.00   1st Qu.:0.00  
#>  Median :209.00   Median :1753   Median :10.00   Median :1.00  
#>  Mean   :215.58   Mean   :1779   Mean   :10.07   Mean   :0.53  
#>  3rd Qu.:209.00   3rd Qu.:1836   3rd Qu.:10.00   3rd Qu.:1.00  
#>  Max.   :408.20   Max.   :1936   Max.   :18.00   Max.   :3.00  
#>  NA's   :1        NA's   :1                                    
#>   IPR_RESPRES    IPR_RESTEMP      IPR_TOTGOR        IPR_WC     
#>  Min.   : 658   Min.   :107.6   Min.   :  404   Min.   : 0.00  
#>  1st Qu.:1246   1st Qu.:206.0   1st Qu.:  595   1st Qu.:51.75  
#>  Median :1404   Median :209.0   Median : 1247   Median :70.00  
#>  Mean   :1386   Mean   :207.3   Mean   : 2028   Mean   :64.73  
#>  3rd Qu.:1565   3rd Qu.:211.0   3rd Qu.: 2348   3rd Qu.:87.53  
#>  Max.   :2727   Max.   :226.0   Max.   :11229   Max.   :96.00  
#>                                                                
#>   IPR_VOGELRT     IPR_VOGELPRES        IPR_PI          GEO_THMD        
#>  Min.   :   0.0   Min.   :   0.0   Min.   : 0.0000   Length:100        
#>  1st Qu.:   0.0   1st Qu.:   0.0   1st Qu.: 0.8261   Class :character  
#>  Median : 559.4   Median : 782.2   Median : 1.7362   Mode  :character  
#>  Mean   : 670.3   Mean   : 659.0   Mean   : 2.6829                     
#>  3rd Qu.:1145.0   3rd Qu.: 982.0   3rd Qu.: 3.4625                     
#>  Max.   :2420.8   Max.   :1381.1   Max.   :12.0000                     
#>                                                                        
#>   GEO_THTEMP          GL_method    GL_ArrayMandrels     GL_Vdepth   
#>  Length:100         Min.   :0.00   Length:100         Min.   :   0  
#>  Class :character   1st Qu.:0.00   Class :character   1st Qu.:1220  
#>  Mode  :character   Median :2.00   Mode  :character   Median :1601  
#>                     Mean   :1.06                      Mean   :2143  
#>                     3rd Qu.:2.00                      3rd Qu.:2304  
#>                     Max.   :2.00                      Max.   :8852  
#>                                                                     
#>      GL_GSG          GL_CO2       WT_DATE             WT_THT         
#>  Min.   :0.800   Min.   :65.0   Length:100         Length:100        
#>  1st Qu.:1.200   1st Qu.:65.0   Class :character   Class :character  
#>  Median :1.200   Median :65.0   Mode  :character   Mode  :character  
#>  Mean   :1.196   Mean   :65.1                                        
#>  3rd Qu.:1.200   3rd Qu.:65.0                                        
#>  Max.   :1.200   Max.   :70.0                                        
#>                                                                      
#>    WT_LIQRT            WT_WC              WT_THP         
#>  Length:100         Length:100         Length:100        
#>  Class :character   Class :character   Class :character  
#>  Mode  :character   Mode  :character   Mode  :character  
#>                                                          
#>                                                          
#>                                                          
#>                                                          
#>     WT_GOR            WT_GLIR            WT_DEPTH        
#>  Length:100         Length:100         Length:100        
#>  Class :character   Class :character   Class :character  
#>  Mode  :character   Mode  :character   Mode  :character  
#>                                                          
#>                                                          
#>                                                          
#>                                                          
#>   WT_Enable          WT_GDEPTH           WT_GPRES        
#>  Length:100         Length:100         Length:100        
#>  Class :character   Class :character   Class :character  
#>  Mode  :character   Mode  :character   Mode  :character  
#>                                                          
#>                                                          
#>                                                          
#>                                                          
#>   WT_RESPRES        ProsperFilename   
#>  Length:100         Length:100        
#>  Class :character   Class :character  
#>  Mode  :character   Mode  :character  
#>                                       
#>                                       
#>                                       
#> 
```

### structure of the data: `str`

``` r
# show the data type structure of the table
str(myXl)
#> Classes 'tbl_df', 'tbl' and 'data.frame':    100 obs. of  51 variables:
#>  $ Wellname         : chr  "PSCO-M005-TS" "PSCO-M0007-TS" "PSCO-M004-LS" "PSCO-M008-TS" ...
#>  $ Company          : chr  "Oil Gains Co." "Oil Gains Co." "Oil Gains Co." "Oil Gains Co." ...
#>  $ Analyst          : chr  "Aida" "Aida" "Aida" "Aida" ...
#>  $ Field            : chr  "PISCO" "PISCO" "PISCO" "PISCO" ...
#>  $ Location         : chr  "M005-TS" "M007-TS" "M004-LS" "M008-TS" ...
#>  $ Platform         : chr  "M" "M" "M" "M" ...
#>  $ Fluid            : num  0 0 0 0 0 0 0 0 0 0 ...
#>  $ WellType         : num  0 0 0 0 0 0 0 0 0 0 ...
#>  $ AL_Method        : num  1 1 1 1 1 0 1 1 1 1 ...
#>  $ Completion       : num  0 0 0 0 0 0 0 0 0 0 ...
#>  $ SandControl      : num  0 0 0 0 0 0 0 0 0 0 ...
#>  $ WT_COUNT         : num  27 22 11 14 13 20 3 2 2 2 ...
#>  $ PVT_GOR          : num  446 473 280 414 420 ...
#>  $ PVT_API          : num  36 36 36 36 35.2 ...
#>  $ PVT_SG_gas       : num  1.2 1.2 1.2 1.2 1.2 ...
#>  $ PVT_WaterSalinity: num  25000 25000 25000 25000 25000 25000 15000 15000 15000 15000 ...
#>  $ PVT_H2S          : num  0 0 0 0 0 0 0 0 0 0 ...
#>  $ PVT_CO2          : num  65.5 65 65 65 65 65 65 65 65 65 ...
#>  $ PVT_PB_CORR      : num  3 3 3 3 3 3 3 3 3 3 ...
#>  $ PVT_VISC_CORR    : num  2 2 2 2 2 2 4 2 0 2 ...
#>  $ PVT_BPTEMP       : num  209 209 209 209 209 209 209 209 209 209 ...
#>  $ PVT_BPPRES       : num  1821 1921 1753 1698 1722 ...
#>  $ VLP_CORR         : num  10 10 1 10 10 10 10 10 10 10 ...
#>  $ IPR_CORR         : num  0 0 1 1 0 0 0 1 1 0 ...
#>  $ IPR_RESPRES      : num  930 1300 1573 1286 1468 ...
#>  $ IPR_RESTEMP      : num  209 209 209 200 209 209 214 211 202 216 ...
#>  $ IPR_TOTGOR       : num  1449 1582 1235 4867 420 ...
#>  $ IPR_WC           : num  66 70 0 5 90 80 90 95 90 90 ...
#>  $ IPR_VOGELRT      : num  384 974 1327 151 1290 ...
#>  $ IPR_VOGELPRES    : num  331 956 941 418 431 ...
#>  $ IPR_PI           : num  4.56 1.15 0.71 0.25 1.35 ...
#>  $ GEO_THMD         : chr  "0|2289.5|" "0|1744|" "0|1954.09|" "0|1720|" ...
#>  $ GEO_THTEMP       : chr  "90|209|" "90|200|" "80|200|" "90|200|" ...
#>  $ GL_method        : num  0 0 2 2 0 2 0 0 0 0 ...
#>  $ GL_ArrayMandrels : chr  "0|0|0|0|0|0|0|0|0|0|" "614.3|1118|1422.5|1564.6|0|0|0|0|0|0|" "167.152|245.913|327.69|373.99|0|0|0|0|0|0|" "560.9|1123.8|1427.6|1569.6|0|0|0|0|0|0|" ...
#>  $ GL_Vdepth        : num  1808 1565 1227 0 1912 ...
#>  $ GL_GSG           : num  1.2 1.2 1.2 1.2 1.2 ...
#>  $ GL_CO2           : num  65 65 65 65 65 65 65 65 65 65 ...
#>  $ WT_DATE          : chr  "09/09/2014|02/07/2012|08/08/2012|02/09/2012|03/10/2012|11/11/2012|08/12/2012|13/12/2012|02/01/2013|18/01/2013|0"| __truncated__ "09/06/2014|21/08/2014|06/02/2012|17/03/2012|11/07/2012|10/08/2012|03/09/2012|05/10/2012|18/11/2012|22/01/2013|1"| __truncated__ "12/02/2004|04/04/2000|04/05/2000|25/07/2000|01/01/2001|03/02/2001|22/02/2001|02/04/2001|01/06/2001|27/11/2003|12/02/2004|" "17/02/2014|02/04/2009|22/05/2009|13/06/2009|03/07/2009|01/08/2009|05/09/2009|19/10/2009|23/10/2009|06/11/2009|0"| __truncated__ ...
#>  $ WT_THT           : chr  "121|112|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|" "125|125|125|125|135|125|125|127|125|125|125|125|125|125|125|125|125|125|125|125|125|122|" "96|99|99|99|99|99|99|99|99|124|99|" "108|108|108|108|108|108|108|108|108|108|108|108|108|108|" ...
#>  $ WT_LIQRT         : chr  "561.2|384.5|365.8|405.3|312.2|501.1|469.9|551.1|887.2|534.7|474.2|408.7|527.2|266.9|377.8|540.6|462.5|540.2|540"| __truncated__ "560|528|711.2|790.6|973.7|732.4|402.5|747.8|793.5|958.9|1190.5|1135.3|909.1|1006.4|980|1013.9|550.6|551.7|591.3"| __truncated__ "382.6|1296|862|739.6|486|1247|208.6|505.8|345.1|1327|382.6|" "150.8|93.9|257.8|213.5|255.1|246.9|218.2|48.4|56.6|96.7|281.2|109.8|127.9|150.8|" ...
#>  $ WT_WC            : chr  "65|66.9|71.08|71.09|75.96|71.1|71.09|68.66|71.1|63.42|71.09|71.08|71.08|26.04|71.09|71.09|71.08|31.1|31.06|31.1"| __truncated__ "70|68|65.94|80.83|75.97|74.75|75.96|75.97|73.09|77.8|76.95|76.94|61.26|75.97|71.09|71.09|71.11|71.1|67.31|68.5|68.5|70.01|" "0|0|0.01|0|0.05|0|3.02|27.98|17.06|0|0|" "5|0|20.36|0|0|0|3.46|0|0|0|9.26|0|15.94|5.01|" ...
#>  $ WT_THP           : chr  "246.5|232.1|246.6|217.6|246.6|217.6|217.6|203|203|203|232.1|232.1|232.1|232.1|261.1|217.6|246.6|232.1|232|232.1"| __truncated__ "246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|" "435|304.5|348|348|334|334|304.5|334|304.5|290|435.1|" "362.6|464.1|507.6|507.6|319.1|304.6|290.1|304.6|304.6|304.6|290.1|319.1|391.6|362.6|" ...
#>  $ WT_GOR           : chr  "3145|1449|2108|2496|4214|4672|3689|3688|4216|542.6|426|4215|4214|460.4|4216|4216|4215|2243|1874|1166|1737|1468|"| __truncated__ "4160|3974|1624.7|336.5|1581.5|287.5|1581|1581.8|1053|1265.5|1265.9|1160.1|759.6|1160.2|1160.1|1632.6|2974.1|408"| __truncated__ "453|573.5|4186|2976|952.7|1848|1347|1227|1015|1235|453.1|" "4867|46172.6|17401.8|16889.5|13548.2|13622.8|16676.7|85862.6|66214.7|59297.7|12641.8|31426.3|5126.4|4867.5|" ...
#>  $ WT_GLIR          : chr  "0|0|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|" "0.5|0.6|0.1|0.1|0.25|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.265|" "0.2|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|" "0|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|" ...
#>  $ WT_DEPTH         : chr  "1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53"| __truncated__ "1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6"| __truncated__ "1227|1227|1227|1227|1227|1227|1227|1227|1227|1227|1227|" "1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|" ...
#>  $ WT_Enable        : chr  "0|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|" "1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|" "1|1|1|1|1|1|1|1|1|0|1|" "1|1|1|1|1|1|1|1|1|1|1|1|1|0|" ...
#>  $ WT_GDEPTH        : chr  "0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|" "0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|" "0|0|0|0|0|0|0|0|0|0|0|" "0|0|0|0|0|0|0|0|0|0|0|0|0|0|" ...
#>  $ WT_GPRES         : chr  "246.5|232.1|246.6|217.6|246.6|217.6|217.6|203|203|203|232.1|232.1|232.1|232.1|261.1|217.6|246.6|232.1|232|232.1"| __truncated__ "246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|" "435|304.5|348|348|334|334|304.5|334|304.5|290|435.1|" "362.6|464.1|507.6|507.6|319.1|304.6|290.1|304.6|304.6|304.6|290.1|319.1|391.6|362.6|" ...
#>  $ WT_RESPRES       : chr  "930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|" "1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|" "1573|1573|1573|1573|1573|1573|1573|1573|1573|1573|1573|" "1286|1025|1025|1025|1025|1025|1025|1025|1025|1025|1025|1025|1025|1025|" ...
#>  $ ProsperFilename  : chr  "\\\\network\\piscis\\well_models\\PISC-M005-TS.Out" "\\\\network\\piscis\\well_models\\PISC-M007-TS.Out" "\\\\network\\piscis\\well_models\\PISC-M004-LL.Out" "\\\\network\\piscis\\well_models\\PISC-M008-TS.Out" ...
```

``` r
# outr table is one of R data structures along with vectors, matrices, arrays and lists.
class(myXl)
#> [1] "tbl_df"     "tbl"        "data.frame"
```

### data types: `typeof`

Let's find out what type of variable we've got in our table:

``` r
typeof(myXl$Wellname)
#> [1] "character"
typeof(myXl$Fluid)
#> [1] "double"
typeof(myXl$IPR_RESTEMP)
#> [1] "double"
```

### using `sapply`, `length`, `sort`

We can do all the column names in one shot with `sapply`.

``` r
dataTypes <- sapply(myXl, typeof, simplify = "array")
typeof(dataTypes)
#> [1] "character"
length(dataTypes)
#> [1] 51
sort(dataTypes)
#>          Wellname           Company           Analyst             Field 
#>       "character"       "character"       "character"       "character" 
#>          Location          Platform          GEO_THMD        GEO_THTEMP 
#>       "character"       "character"       "character"       "character" 
#>  GL_ArrayMandrels           WT_DATE            WT_THT          WT_LIQRT 
#>       "character"       "character"       "character"       "character" 
#>             WT_WC            WT_THP            WT_GOR           WT_GLIR 
#>       "character"       "character"       "character"       "character" 
#>          WT_DEPTH         WT_Enable         WT_GDEPTH          WT_GPRES 
#>       "character"       "character"       "character"       "character" 
#>        WT_RESPRES   ProsperFilename             Fluid          WellType 
#>       "character"       "character"          "double"          "double" 
#>         AL_Method        Completion       SandControl          WT_COUNT 
#>          "double"          "double"          "double"          "double" 
#>           PVT_GOR           PVT_API        PVT_SG_gas PVT_WaterSalinity 
#>          "double"          "double"          "double"          "double" 
#>           PVT_H2S           PVT_CO2       PVT_PB_CORR     PVT_VISC_CORR 
#>          "double"          "double"          "double"          "double" 
#>        PVT_BPTEMP        PVT_BPPRES          VLP_CORR          IPR_CORR 
#>          "double"          "double"          "double"          "double" 
#>       IPR_RESPRES       IPR_RESTEMP        IPR_TOTGOR            IPR_WC 
#>          "double"          "double"          "double"          "double" 
#>       IPR_VOGELRT     IPR_VOGELPRES            IPR_PI         GL_method 
#>          "double"          "double"          "double"          "double" 
#>         GL_Vdepth            GL_GSG            GL_CO2 
#>          "double"          "double"          "double"
```

### An inventory of the kind of data we have: `table`

``` r
table(dataTypes)
#> dataTypes
#> character    double 
#>        22        29
```

``` r
library(Hmisc)
#> Loading required package: lattice
#> Loading required package: survival
#> Loading required package: Formula
#> Loading required package: ggplot2
#> 
#> Attaching package: 'Hmisc'
#> The following objects are masked from 'package:base':
#> 
#>     format.pval, round.POSIXt, trunc.POSIXt, units
```

``` r
describe(myXl)
#> Warning in min(diff(sort(unique(xnum)))): no non-missing arguments to min;
#> returning Inf

#> Warning in min(diff(sort(unique(xnum)))): no non-missing arguments to min;
#> returning Inf

#> Warning in min(diff(sort(unique(xnum)))): no non-missing arguments to min;
#> returning Inf
#> myXl 
#> 
#>  51  Variables      100  Observations
#> ---------------------------------------------------------------------------
#> Wellname 
#>        n  missing distinct 
#>      100        0       98 
#> 
#> lowest : PiSCO-R009-SS PISCO-R027-LS PSCO-027-TS   PSCO-M0007-TS PSCO-M001-TS 
#> highest: PSCO-S030-LS  PSCO-S030-SS  PSCO-S031-TS  PSCO-S032-LS  PSCO-S032-SS 
#> ---------------------------------------------------------------------------
#> Company 
#>             n       missing      distinct         value 
#>           100             0             1 Oil Gains Co. 
#>                         
#> Value      Oil Gains Co.
#> Frequency            100
#> Proportion             1
#> ---------------------------------------------------------------------------
#> Analyst 
#>        n  missing distinct 
#>       99        1       15 
#> 
#> Aida (8, 0.081), Americo (6, 0.061), Andrew (9, 0.091), Andy (2, 0.020),
#> Camden (14, 0.141), Ibironk (1, 0.010), Ibironke (11, 0.111), Kai (8,
#> 0.081), Norman (9, 0.091), Rod (3, 0.030), Rodrigo (2, 0.020), Sam (1,
#> 0.010), Thomas (1, 0.010), Tom (7, 0.071), Vivek (17, 0.172)
#> ---------------------------------------------------------------------------
#> Field 
#>        n  missing distinct 
#>       99        1        2 
#>                       
#> Value      pisco PISCO
#> Frequency      2    97
#> Proportion  0.02  0.98
#> ---------------------------------------------------------------------------
#> Location 
#>        n  missing distinct 
#>       99        1       97 
#> 
#> lowest : M001-TS M004-LS M005-TS M006-TS M007-TS
#> highest: S030-LS S030-SS S031-TS S032-LS S032-SS
#> ---------------------------------------------------------------------------
#> Platform 
#>        n  missing distinct 
#>       98        2        4 
#>                                   
#> Value          M     Q     R     S
#> Frequency     20    24    28    26
#> Proportion 0.204 0.245 0.286 0.265
#> ---------------------------------------------------------------------------
#> Fluid 
#>        n  missing distinct     Info     Mean      Gmd 
#>      100        0        1        0        0        0 
#>               
#> Value        0
#> Frequency  100
#> Proportion   1
#> ---------------------------------------------------------------------------
#> WellType 
#>        n  missing distinct     Info     Mean      Gmd 
#>      100        0        1        0        0        0 
#>               
#> Value        0
#> Frequency  100
#> Proportion   1
#> ---------------------------------------------------------------------------
#> AL_Method 
#>        n  missing distinct     Info      Sum     Mean      Gmd 
#>      100        0        2    0.059       98     0.98   0.0396 
#> 
#> ---------------------------------------------------------------------------
#> Completion 
#>        n  missing distinct     Info      Sum     Mean      Gmd 
#>      100        0        2    0.195        7     0.07   0.1315 
#> 
#> ---------------------------------------------------------------------------
#> SandControl 
#>        n  missing distinct     Info     Mean      Gmd 
#>      100        0        2    0.221     0.24   0.4461 
#>                     
#> Value         0    3
#> Frequency    92    8
#> Proportion 0.92 0.08
#> ---------------------------------------------------------------------------
#> WT_COUNT 
#>        n  missing distinct     Info     Mean      Gmd      .05      .10 
#>      100        0       19    0.968     4.82    4.886     1.00     1.00 
#>      .25      .50      .75      .90      .95 
#>     1.00     3.00     7.00    11.10    14.05 
#>                                                                       
#> Value         1    2    3    4    5    6    7    8    9   10   11   12
#> Frequency    28   16   17    8    2    3    2    4    4    3    3    3
#> Proportion 0.28 0.16 0.17 0.08 0.02 0.03 0.02 0.04 0.04 0.03 0.03 0.03
#>                                              
#> Value        13   14   15   19   20   22   27
#> Frequency     1    1    1    1    1    1    1
#> Proportion 0.01 0.01 0.01 0.01 0.01 0.01 0.01
#> ---------------------------------------------------------------------------
#> PVT_GOR 
#>        n  missing distinct     Info     Mean      Gmd      .05      .10 
#>      100        0       21     0.99    431.2    25.94    413.6    413.6 
#>      .25      .50      .75      .90      .95 
#>    416.0    423.0    455.2    456.9    472.9 
#>                                                                       
#> Value      280.0 350.0 413.0 413.5 414.0 415.0 416.0 419.0 420.0 426.0
#> Frequency      1     1     1     8     2     1    22     3    11    12
#> Proportion  0.01  0.01  0.01  0.08  0.02  0.01  0.22  0.03  0.11  0.12
#>                                                     
#> Value      439.0 445.5 446.0 450.5 455.0 472.0 473.0
#> Frequency      1     3     2     5    17     2     8
#> Proportion  0.01  0.03  0.02  0.05  0.17  0.02  0.08
#> ---------------------------------------------------------------------------
#> PVT_API 
#>        n  missing distinct     Info     Mean      Gmd 
#>      100        0        9    0.504    36.15   0.3643 
#>                                                                           
#> Value      35.0000 35.2000 36.0000 36.1000 36.6000 36.8000 37.0000 39.0000
#> Frequency        1       1      79      14       1       1       1       1
#> Proportion    0.01    0.01    0.79    0.14    0.01    0.01    0.01    0.01
#>                   
#> Value      46.1535
#> Frequency        1
#> Proportion    0.01
#> ---------------------------------------------------------------------------
#> PVT_SG_gas 
#>        n  missing distinct     Info     Mean      Gmd 
#>      100        0        4    0.595    1.221  0.04603 
#>                                           
#> Value      0.80000 1.20000 1.21562 1.30000
#> Frequency        1      73       1      25
#> Proportion    0.01    0.73    0.01    0.25
#> ---------------------------------------------------------------------------
#> PVT_WaterSalinity 
#>        n  missing distinct     Info     Mean      Gmd 
#>      100        0        9    0.835    15247     4136 
#>                                                                 
#> Value       1000 10000 12000 15000 15500 16700 20000 25000 30000
#> Frequency      1    17     3    54    12     1     1     9     2
#> Proportion  0.01  0.17  0.03  0.54  0.12  0.01  0.01  0.09  0.02
#> ---------------------------------------------------------------------------
#> PVT_H2S 
#>        n  missing distinct     Info     Mean      Gmd 
#>      100        0        1        0        0        0 
#>               
#> Value        0
#> Frequency  100
#> Proportion   1
#> ---------------------------------------------------------------------------
#> PVT_CO2 
#>        n  missing distinct     Info     Mean      Gmd 
#>      100        0        8    0.669    66.58    3.684 
#>                                                           
#> Value      29.00 65.00 65.50 69.00 70.00 73.00 74.00 74.28
#> Frequency      1    69     1     4    11     4     9     1
#> Proportion  0.01  0.69  0.01  0.04  0.11  0.04  0.09  0.01
#> ---------------------------------------------------------------------------
#> PVT_PB_CORR 
#>        n  missing distinct     Info     Mean      Gmd 
#>      100        0        3    0.318     2.78   0.4053 
#>                          
#> Value         0    2    3
#> Frequency     5    7   88
#> Proportion 0.05 0.07 0.88
#> ---------------------------------------------------------------------------
#> PVT_VISC_CORR 
#>        n  missing distinct     Info     Mean      Gmd 
#>      100        0        5    0.759     1.77   0.8438 
#>                                    
#> Value         0    1    2    3    4
#> Frequency     7   24   61    1    7
#> Proportion 0.07 0.24 0.61 0.01 0.07
#> ---------------------------------------------------------------------------
#> PVT_BPTEMP 
#>        n  missing distinct     Info     Mean      Gmd      .05      .10 
#>       99        1       10    0.686    215.6     18.4      208      208 
#>      .25      .50      .75      .90      .95 
#>      208      209      209      209      209 
#>                                               
#> Value         98   203   206   208   209   408
#> Frequency      1     1     2    22    69     4
#> Proportion 0.010 0.010 0.020 0.222 0.697 0.040
#> ---------------------------------------------------------------------------
#> PVT_BPPRES 
#>        n  missing distinct     Info     Mean      Gmd      .05      .10 
#>       99        1       28    0.995     1779    74.55     1698     1698 
#>      .25      .50      .75      .90      .95 
#>     1722     1753     1836     1865     1921 
#>                                                                          
#> Value      1683.5 1698.0 1722.0 1731.5 1736.5 1738.5 1746.0 1753.0 1767.5
#> Frequency       1     10     15      3      1      5      8     18      1
#> Proportion  0.010  0.101  0.152  0.030  0.010  0.051  0.081  0.182  0.010
#>                                                                   
#> Value      1808.5 1821.0 1821.5 1835.5 1836.0 1850.5 1921.0 1935.5
#> Frequency       2      6      1      2      8      8      9      1
#> Proportion  0.020  0.061  0.010  0.020  0.081  0.081  0.091  0.010
#> ---------------------------------------------------------------------------
#> VLP_CORR 
#>        n  missing distinct     Info     Mean      Gmd 
#>      100        0        5    0.246    10.07    1.262 
#>                                    
#> Value         0    1   10   12   18
#> Frequency     2    1   91    2    4
#> Proportion 0.02 0.01 0.91 0.02 0.04
#> ---------------------------------------------------------------------------
#> IPR_CORR 
#>        n  missing distinct     Info     Mean      Gmd 
#>      100        0        3    0.757     0.53   0.5448 
#>                          
#> Value         0    1    3
#> Frequency    49   50    1
#> Proportion 0.49 0.50 0.01
#> ---------------------------------------------------------------------------
#> IPR_RESPRES 
#>        n  missing distinct     Info     Mean      Gmd      .05      .10 
#>      100        0       84        1     1386    285.6      926     1036 
#>      .25      .50      .75      .90      .95 
#>     1246     1403     1565     1627     1666 
#> 
#> lowest :  658.000  800.000  810.000  850.000  850.000
#> highest: 1685.996 1695.696 1695.700 1750.000 2727.000
#> ---------------------------------------------------------------------------
#> IPR_RESTEMP 
#>        n  missing distinct     Info     Mean      Gmd      .05      .10 
#>      100        0       36    0.969    207.3    9.458    200.0    204.8 
#>      .25      .50      .75      .90      .95 
#>    206.0    209.0    211.0    215.1    218.5 
#> 
#> lowest : 107.578 121.756 159.000 200.000 201.000
#> highest: 218.400 220.000 223.000 224.000 226.000
#> ---------------------------------------------------------------------------
#> IPR_TOTGOR 
#>        n  missing distinct     Info     Mean      Gmd      .05      .10 
#>      100        0       85        1     2028     2047    425.7    500.0 
#>      .25      .50      .75      .90      .95 
#>    595.0   1247.0   2347.8   4828.3   7445.9 
#> 
#> lowest :   404.000   413.554   415.000   415.875   420.000
#> highest:  7500.000  7727.000  7737.000 10424.000 11229.000
#> ---------------------------------------------------------------------------
#> IPR_WC 
#>        n  missing distinct     Info     Mean      Gmd      .05      .10 
#>      100        0       54    0.998    64.73    29.14    2.741   18.900 
#>      .25      .50      .75      .90      .95 
#>   51.750   70.000   87.528   90.405   95.000 
#> 
#> lowest :  0.00  2.00  2.78  5.00  8.00, highest: 90.40 90.45 90.47 95.00 96.00
#> ---------------------------------------------------------------------------
#> IPR_VOGELRT 
#>        n  missing distinct     Info     Mean      Gmd      .05      .10 
#>      100        0       72    0.982    670.3    691.2      0.0      0.0 
#>      .25      .50      .75      .90      .95 
#>      0.0    559.4   1145.0   1492.8   1803.8 
#> 
#> lowest :    0.00  100.00  150.80  200.00  210.40
#> highest: 1891.10 1932.00 2131.50 2398.00 2420.77
#> ---------------------------------------------------------------------------
#> IPR_VOGELPRES 
#>        n  missing distinct     Info     Mean      Gmd      .05      .10 
#>      100        0       75    0.982      659      492      0.0      0.0 
#>      .25      .50      .75      .90      .95 
#>      0.0    782.2    982.0   1143.5   1217.3 
#> 
#> lowest :    0.000  331.000  364.696  418.464  430.877
#> highest: 1261.650 1310.000 1328.500 1328.700 1381.096
#> ---------------------------------------------------------------------------
#> IPR_PI 
#>        n  missing distinct     Info     Mean      Gmd      .05      .10 
#>      100        0       81        1    2.683    2.611   0.2375   0.5720 
#>      .25      .50      .75      .90      .95 
#>   0.8261   1.7362   3.4625   6.9274   7.8100 
#> 
#> lowest :  0.00  0.25  0.37  0.40  0.50, highest:  8.00  8.90  9.00 10.00 12.00
#> ---------------------------------------------------------------------------
#> GEO_THMD 
#>        n  missing distinct 
#>      100        0       96 
#> 
#> lowest : 0|100|1891|    0|1000|1541.4| 0|1200|1299.7| 0|1254.8|      0|1260.4|     
#> highest: 14.52|1684.5|  14.52|1781.52| 14.52|1914.32| 14.52|1954|    14.6|2423.5|  
#> ---------------------------------------------------------------------------
#> GEO_THTEMP 
#>        n  missing distinct 
#>      100        0       65 
#> 
#> lowest : 104|216|               104|218|               122|208.004|           140|206|               140|208|              
#> highest: 90|214|                91.653|207.696|213.54| 92|159|                92|214|                95|203|               
#> ---------------------------------------------------------------------------
#> GL_method 
#>        n  missing distinct     Info     Mean      Gmd 
#>      100        0        2    0.747     1.06    1.006 
#>                     
#> Value         0    2
#> Frequency    47   53
#> Proportion 0.47 0.53
#> ---------------------------------------------------------------------------
#> GL_ArrayMandrels 
#>        n  missing distinct 
#>      100        0       84 
#> 
#> lowest : 0|0|0|0|0|0|0|0|0|0|                                     0|0|0|1197.8|1356.57|0|0|0|0|0|                          0|0|0|1203.1|1366.1|0|0|0|0|0|                           1112.2|1213.2|1647.3|1800.9|0|0|0|0|0|0|                 1139|0|0|0|0|0|0|0|0|0|                                 
#> highest: 796|1345|1748.5|2033|2242.9|0|0|0|0|0|                   808.4|1423.9|1834.9|2175.7|2252.5|0|0|0|0|0|             846.1|1260|1605.8|1864.7|0|0|0|0|0|0|                    915.354|1702.76|2526.25|3382.55|4265.09|5167.32|0|0|0|0| 928.15|1580.45|2022.22|2319.51|0|0|0|0|0|0|             
#> ---------------------------------------------------------------------------
#> GL_Vdepth 
#>        n  missing distinct     Info     Mean      Gmd      .05      .10 
#>      100        0       81    0.998     2143     1873        0        0 
#>      .25      .50      .75      .90      .95 
#>     1220     1601     2304     5020     5774 
#> 
#> lowest :    0.000  284.000  418.000  603.500  841.000
#> highest: 5774.278 6826.771 7542.651 7939.305 8852.034
#> ---------------------------------------------------------------------------
#> GL_GSG 
#>        n  missing distinct     Info     Mean      Gmd 
#>      100        0        2     0.03    1.196    0.008 
#>                     
#> Value       0.8  1.2
#> Frequency     1   99
#> Proportion 0.01 0.99
#> ---------------------------------------------------------------------------
#> GL_CO2 
#>        n  missing distinct     Info     Mean      Gmd 
#>      100        0        2    0.059     65.1    0.198 
#>                     
#> Value        65   70
#> Frequency    98    2
#> Proportion 0.98 0.02
#> ---------------------------------------------------------------------------
#> WT_DATE 
#>        n  missing distinct 
#>       98        2       97 
#> 
#> lowest : |||01/03/2014| ||01/05/2014|  ||06/05/2014|  ||06/09/2014|  |01/05/2013|  
#> highest: 41918          41953          41982          42005          42065         
#> ---------------------------------------------------------------------------
#> WT_THT 
#>        n  missing distinct 
#>      100        0       96 
#> 
#> lowest : 100                                102|109|109|115|                   103                                104|150|                           104|186.8|102.2|                  
#> highest: 87|176|98.6|                       91                                 93|165.2|125|                      95|116.96|89.6|                    96|99|99|99|99|99|99|99|99|124|99|
#> ---------------------------------------------------------------------------
#> WT_LIQRT 
#>        n  missing distinct 
#>      100        0       97 
#> 
#> lowest : 1039|867.352|              1057|776|1065|             1057|776|1932|             1082.199951172             1087|1087|1353.8|         
#> highest: 863                        900|1290|1347|1155|        900|714.76|                900|814.8|607.5|683.4|700| 968|580|                  
#> ---------------------------------------------------------------------------
#> WT_WC 
#>        n  missing distinct 
#>      100        0       94 
#> 
#> lowest : 0                                                                           0|0|0.01|0|0.05|0|3.02|27.98|17.06|0|0|                                     0|0|0|0|0|19|20|17|                                                         0|0|0|0|0|74|71|71|70|                                                      0|0|0|0|20|50|65|80|50|60|34.72|40|                                        
#> highest: 91.199996948                                                                92|92.5|                                                                    94|80|80|90|                                                                95.13|92|90.46|90.46|92.83|90.46|95.19|71.14|88.69|60.59|75.74|90.46|90.46| 95|95|                                                                     
#> ---------------------------------------------------------------------------
#> WT_THP 
#>        n  missing distinct 
#>      100        0       92 
#> 
#> lowest : 100|80.696|                                                                          101.5|101.53|101.5|261|87|80|87|101.5|87|87|87|                                      101.5|102|                                                                           101.5|188.5|246.5|                                                                   102|87|                                                                             
#> highest: 348.100006104                                                                        362.5                                                                                362.6|464.1|507.6|507.6|319.1|304.6|290.1|304.6|304.6|304.6|290.1|319.1|391.6|362.6| 435|304.5|348|348|334|334|304.5|334|304.5|290|435.1|                                 87                                                                                  
#> ---------------------------------------------------------------------------
#> WT_GOR 
#>        n  missing distinct 
#>      100        0       99 
#> 
#> lowest : 1000|2674|2674|                        1009|2378|                             1050|1800|837|112|159|500|5056|667|    1108|2230|1051|2501|2705|272|642|2700| 1114.900024414                        
#> highest: 9001|540|530|                          9003                                   952                                    953|6687|957|700|5654|1119|            977|1500|                             
#> ---------------------------------------------------------------------------
#> WT_GLIR 
#>        n  missing distinct 
#>      100        0       90 
#> 
#> lowest : 0                                                            0.033|0|0.2161|0.339|                                        0.04|0.6|0.56|0.75|0.06|0.48|0.35|                           0.096|0.047|0|0.05|0.05|0.43|0.24|0.29|0.11|                 0.096|0.047|0|0.05|0.05|0.96|0.47|0.17|                     
#> highest: 0|0|0|0.27|0|0|0|0.23|0.1|0.36|                              0|0|0|0.35494|0.35494|0.35494|0.35494|0.35494|0.1|0.3|       0|0|0|0|0|0.63889|0.63889|0.63889|0.63889|0.63889|0.305|0.6| 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|                     475|430|550|0.27|                                           
#> ---------------------------------------------------------------------------
#> WT_DEPTH 
#>        n  missing distinct 
#>      100        0       96 
#> 
#> lowest : 0                                                                0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|                         0|0|0|0|0|1605|1605|1605|1605|1605|1605|1605|                    0|0|0|1184|1184|1184|1184|1184|1184|1184|                        0|0|0|1315.1|1315.1|1315.1|                                     
#> highest: 683.6|2030.5|                                                    6955.05|6955.05|6955.05|                                         7542.65|7542.65|7542.65|7542.65|7542.65|7542.65|7542.65|7542.65| 856|841|                                                         886.000021875                                                   
#> ---------------------------------------------------------------------------
#> WT_Enable 
#>        n  missing distinct 
#>      100        0       26 
#> 
#> lowest : 0                                            0|1|                                         0|1|1|                                       0|1|1|1|1|1|1|1|1|                           0|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|      
#> highest: 1|1|1|1|1|1|1|1|1|1|1|0|                     1|1|1|1|1|1|1|1|1|1|1|1|1|0|                 1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|               1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|1|1|1|     1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> ---------------------------------------------------------------------------
#> WT_GDEPTH 
#>        n  missing distinct 
#>      100        0       57 
#> 
#> lowest : 0                                                                          0.3048|0.3048|0.3048|0.3048|0.3048|0.3048|0.3048|0.3048|429.555|1504.47|0| 0|0|                                                                       0|0|0|                                                                     0|0|0|0|                                                                  
#> highest: 6279.53|0|6279.53|                                                         6542.98|0|0|                                                               7273.62|0|7273.62|                                                         7372.047363281                                                             9484.91|0|0|0|0|0|9500.98|9500.98|0|0|                                    
#> ---------------------------------------------------------------------------
#> WT_GPRES 
#>        n  missing distinct 
#>      100        0       92 
#> 
#> lowest : 0.14504|0.14504|0.14504|0.14504|0.14504|0.14504|0.14504|0.14504|0.14504|0.14504|660.26|217.56| 0.14504|0.14504|0.14504|0.14504|0.14504|0.14504|0.14504|0.14504|1392.86|290|                   101.5|101.53|101.5|261|87|80|87|101.5|87|87|87|                                                101.5|102|                                                                                     101.5|188.5|246.5|                                                                            
#> highest: 87                                                                                             917.006|245.696|743.749|                                                                       936.089981934                                                                                  980|980|980|980|980|980|980|980|980|823.991|1004.74|276|                                       982.195|710.317|705.396|188.5|218|218|                                                        
#> ---------------------------------------------------------------------------
#> WT_RESPRES 
#>        n  missing distinct 
#>      100        0       96 
#> 
#> lowest : 1028.787597656                                                                                               1034|1034|1034|                                                                                              1036                                                                                                         1058.259964844                                                                                               1080                                                                                                        
#> highest: 850                                                                                                          930.314331055                                                                                                930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930| 949.696|1114.7|1114.7|                                                                                       969.233|1480|1480|1480|1480|1480|                                                                           
#> ---------------------------------------------------------------------------
#> ProsperFilename 
#>        n  missing distinct 
#>      100        0      100 
#> 
#> lowest : \\network\piscis\well_models\PISC-M001-TS.Out \\network\piscis\well_models\PISC-M002-LS.Out \\network\piscis\well_models\PISC-M004-LL.Out \\network\piscis\well_models\PISC-M005-TS.Out \\network\piscis\well_models\PISC-M006-TS.Out
#> highest: \\network\piscis\well_models\PISC-S030-SS.Out \\network\piscis\well_models\PISC-S031.Out    \\network\piscis\well_models\PISC-S032-LS.Out \\network\piscis\well_models\PISC-S032-SS.Out \\network\piscis\well_models\PISCS002.out    
#> ---------------------------------------------------------------------------
```
