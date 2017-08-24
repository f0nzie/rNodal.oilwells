
<!-- README.md is generated from README.Rmd. Please edit that file -->
Finding and filling missing data: alphanumeric
==============================================

``` r
# load the library xlsx
library(xlsx)
#> Loading required package: rJava
#> Loading required package: xlsxjars

# read the raw data
myXl <- read.xlsx("../extdata/oilfield_100w_raw_data.xlsx", 
                  sheetIndex = 1, stringsAsFactors=FALSE)
```

Mistyped data
-------------

One of the challenges in cleaning up well data is having uniform and standard well names. This becomes important at the time of classification, ranking and selection. An example of this is when looking for the **top 20** oil producers or wells with higher **watercut** or **GOR** or wells with highest or lowest gas injection rate **GLIR** (gas lift wells). If a well name is not correct you may encounter repeated occurrences of the well, a wrong classificatio, or a well that should have received attention but did not. Besides, how good an analysis can be if we start with typos in the well names, or the well everyone is expecting doesn't show up in the plot or summary?

One of the first things to do, if we are folowing a well name standard, internal or API, is finding if all the wells in the raw data file are compliant. One way of doing it is comparing the well names with a pattern. In R there are several functions that use patterns for name verification and correction. We will be using a few: `grep`, `grepl`, `gsub`, and couple more from the R package `stringr`.

Let's start then defining the pattern of a well name.

Pattern detection
-----------------

If we take a look at the well name in the picture at the top we see that the naming should follow these rules:

-   the first 4 alphabetic characters represent the abbreviation of the field
-   then , there is dash
-   after the dash comes one character for the platform
-   then 3 digits, from 000 to 999 that represent the well number
-   then a dash
-   and finally, two alphabetic characters for the completion type

So, there is a total of 10 significant identifiers plus 2 dashes.

If we use `regular expressions` or `regex` in its simplest form the wells should follow this pattern:

           PSCO-[M,Q,R,S][0-9][0-9][0-9]-[T,L,S]S

``` r
# using a template to find out which well names do not follow a pattern
  x <- myXl$Wellname
  pattern <- "PSCO-[M,O,P,,Q,R,S][0-9][0-9][0-9]-[T,L,S]S"
  result  <- grep(pattern, x, value = TRUE, invert = TRUE)
  indices <- grep(pattern, x, invert = TRUE)
  data.frame(indices, result)
#>    indices        result
#> 1        2 PSCO-M0007-TS
#> 2        7  PSCO-m016-LS
#> 3       22   PSCO-Q001-S
#> 4       30   PSCO-Q019-L
#> 5       45 PiSCO-R009-SS
#> 6       46  PSCO-r015-LS
#> 7       66 PISCO-R027-LS
#> 8       69   PSCO-R022-T
#> 9       75   PSCO-027-TS
#> 10      82 PSCO-S019 -LS
#> 11     100 PSCO-M0026-TS
```

``` r
# if we want to add another column for extra information just add the column with the indices
data.frame(indices, result, myXl$Platform[indices])
#>    indices        result myXl.Platform.indices.
#> 1        2 PSCO-M0007-TS                      M
#> 2        7  PSCO-m016-LS                      M
#> 3       22   PSCO-Q001-S                      Q
#> 4       30   PSCO-Q019-L                      Q
#> 5       45 PiSCO-R009-SS                      R
#> 6       46  PSCO-r015-LS                      R
#> 7       66 PISCO-R027-LS                      R
#> 8       69   PSCO-R022-T                      R
#> 9       75   PSCO-027-TS                      S
#> 10      82 PSCO-S019 -LS                      S
#> 11     100 PSCO-M0026-TS                   <NA>
```

The result is that we get the observations (rows) that have incorrect well names. They are 11 instances.

This is much better than visually inspecting them in a spreadsheet, isn't it?

What are the type of offences?

-   Incorrect well number: `PSCO-M0007-TS`, `PSCO-M0026-TS`
-   Platform omitted: `PSCO-027-TS`
-   Platform in lowercase: `PSCO-r015-LS`, `PSCO-m016-LS`
-   Incorrect field name: `PiSCO-R009-SS`, `PISCO-R027-LS`
-   Incorrect completion type: `PSCO-R022-T`, `PSCO-Q019-L`, `PSCO-Q001-S`
-   Extra spaces in the name: `PSCO-S019 -LS`, `PSCO- M010-SS`

Fix the well name
-----------------

We will see that some well names can be fixed manually and others should be done automatically with a script.

In our particular case we only have 100 wells but what about if we have 1000, or 5000? Doing it manually is not an option. Some are quickly fixable some others are more challenging. Let's start by the easier ones.

> Always go from the more general to the more particular.

Let's convert the names to uppercase and verify how many were corrected.

``` r
# lowercase to uppercase
  myXl$Wellname <- toupper(myXl$Wellname)

# show the wells with issues
  x       <- myXl$Wellname
  pattern <- "PSCO-[M,O,P,,Q,R,S][0-9][0-9][0-9]-[T,L,S]S"
  indices <- grep(pattern, x, invert = TRUE)
  result  <- grep(pattern, x, value = TRUE, invert = TRUE)
  data.frame(indices, result)
#>   indices        result
#> 1       2 PSCO-M0007-TS
#> 2      22   PSCO-Q001-S
#> 3      30   PSCO-Q019-L
#> 4      45 PISCO-R009-SS
#> 5      66 PISCO-R027-LS
#> 6      69   PSCO-R022-T
#> 7      75   PSCO-027-TS
#> 8      82 PSCO-S019 -LS
#> 9     100 PSCO-M0026-TS
```

Two were corrected.

Now, let's remove spaces.

``` r
# removing spaces
  x         <- myXl$Wellname
  pattern   <- " "
  replaceBy <- ""
  myXl$Wellname <- gsub(pattern, replaceBy, x)

# show the wells with issues
  # myXl[!grepl("PSCO-[M,O,P,,Q,R,S][0-9][0-9][0-9]-[T,L,S]S", myXl$Wellname),]
  
# show the wells with issues
  x       <- myXl$Wellname
  pattern <- "PSCO-[M,O,P,,Q,R,S][0-9][0-9][0-9]-[T,L,S]S"
  indices <- grep(pattern, x, invert = TRUE)
  result  <- grep(pattern, x, value = TRUE, invert = TRUE)
  data.frame(indices, result)  
#>   indices        result
#> 1       2 PSCO-M0007-TS
#> 2      22   PSCO-Q001-S
#> 3      30   PSCO-Q019-L
#> 4      45 PISCO-R009-SS
#> 5      66 PISCO-R027-LS
#> 6      69   PSCO-R022-T
#> 7      75   PSCO-027-TS
#> 8     100 PSCO-M0026-TS
```

One well name was corrected.

Correct the completion type. Tey should have two characters: LS, TS or SS.

``` r
# complete the completion type
# We have three completion type: SS, LS and TS

  myXl$Wellname <- gsub("-L$", "-LS", myXl$Wellname)    # the dollar sign at the end, means that 
  myXl$Wellname <- gsub("-S$", "-SS", myXl$Wellname)    # we are checking at the end of the string
  myXl$Wellname <- gsub("-T$", "-TS", myXl$Wellname)

# show the wells with issues
  x <- myXl$Wellname
  pattern <- "PSCO-[M,O,P,,Q,R,S][0-9][0-9][0-9]-[T,L,S]S"
  result  <- grep(pattern, x, value = TRUE, invert = TRUE)
  indices <- grep(pattern, x, invert = TRUE)
  data.frame(indices, result)
#>   indices        result
#> 1       2 PSCO-M0007-TS
#> 2      45 PISCO-R009-SS
#> 3      66 PISCO-R027-LS
#> 4      75   PSCO-027-TS
#> 5     100 PSCO-M0026-TS
```

Those were the easy ones. We had three corrections. There are 5 more to go.

### correcting the field in the well name

There are two wells that were not properly field identified.

We have an additional "I" in the field name abbreviation. We have to remove it.

At this point we have two choices: (1) change all the first 4 first characters to PSCO, or, (2) replace only those two well names with the issue.

``` r
# detect well names that are not named as PSCO-
  x       <- myXl$Wellname
  pattern <- "^PSCO-"
  result  <- grep(pattern, x, value = TRUE, invert = TRUE)
  indices <- grep(pattern, x, invert = TRUE)
  data.frame(indices, result)
#>   indices        result
#> 1      45 PISCO-R009-SS
#> 2      66 PISCO-R027-LS
  
# 
# !    logical negation
#  ^   means look at the start of the string
  rx <- result
```

#### option (1): change all the first 4 first characters to PSCO

``` r
# replace any characters before the first dash
  x       <- myXl$Wellname
  pattern <- "^[^-]+"
  replace <- "PSCO"

# replace on all the wells  
  myXl$Wellname <- gsub(pattern, replace, x, perl = TRUE)
```

#### option (2): replace only those two well names with the issue.

``` r
# replace the letter "I" by a blank
  x       <- myXl$Wellname
  pattern <- "I(?<!S)"
  replaceBy <- ""

# replace on indexed wells
  myXl$Wellname[indices]
#> [1] "PSCO-R009-SS" "PSCO-R027-LS"
  myXl$Wellname[indices] <- gsub(pattern, replaceBy, x[indices], perl = TRUE)
  myXl$Wellname[indices]
#> [1] "PSCO-R009-SS" "PSCO-R027-LS"
```

correct the length of the well number
-------------------------------------

The well names have corrected on the field identifier. Next if correct the length of the well number.

``` r
# show the wells with issues
  x       <- myXl$Wellname
  pattern <- "PSCO-[M,O,P,,Q,R,S][0-9][0-9][0-9]-[T,L,S]S"
  result  <- grep(pattern, x, value = TRUE, invert = TRUE)
  indices <- grep(pattern, x, invert = TRUE)
  data.frame(indices, result, platform = myXl$Platform[indices])
#>   indices        result platform
#> 1       2 PSCO-M0007-TS        M
#> 2      75   PSCO-027-TS        S
#> 3     100 PSCO-M0026-TS     <NA>
```

Alright. So far, we have corrected the field name in the well name. There are still three more wells to go which problems are:

    PSCO-M0007-TS  long well number. It should be maximum of 3 digits
    PSCO-027-TS    missing platform number
    PSCO-M0026-TS  long well number. It should be maximum of 3 digits

### correcting longer well number (digits)

They should be `000` to `999` after the field identifier (one character)

``` r
# take a look at the wells that have longer digits
  x <- myXl$Wellname
  pattern = "(?=[0-9]{4,})0(?=0)" 
  
  values  <- grep(pattern, x, value = TRUE, perl = TRUE)
  indices <- grep(pattern, x, perl = TRUE)
  data.frame(indices, values)
#>   indices        values
#> 1       2 PSCO-M0007-TS
#> 2     100 PSCO-M0026-TS
```

See what we are going to replace:

``` r
# what the pattern has detected is one zero at position 7, right after the field
  gregexpr(pattern, result, perl = TRUE)
#> [[1]]
#> [1] 7
#> attr(,"match.length")
#> [1] 1
#> attr(,"useBytes")
#> [1] TRUE
#> 
#> [[2]]
#> [1] -1
#> attr(,"match.length")
#> [1] -1
#> attr(,"useBytes")
#> [1] TRUE
#> 
#> [[3]]
#> [1] 7
#> attr(,"match.length")
#> [1] 1
#> attr(,"useBytes")
#> [1] TRUE
```

``` r
# replace well number that are long
x         <- myXl$Wellname
pattern   <-  "(?=[0-9]{4,})0(?=0)"      
replaceBy <-  ""

myXl$Wellname[indices] <- gsub(pattern, replaceBy, x[indices], perl = TRUE)
```

``` r
# show the wells with issues
  x <- myXl$Wellname
  pattern <- "PSCO-[M,O,P,,Q,R,S][0-9][0-9][0-9]-[T,L,S]S"
  values  <- grep(pattern, x, value = TRUE, invert = TRUE)
  indices <- grep(pattern, x, invert = TRUE)
  data.frame(indices, values)
#>   indices      values
#> 1      75 PSCO-027-TS
```

Very good. Now we have one well left.

Add the one-letter platform identifier to the well name
-------------------------------------------------------

``` r
# take a look at the wells 
  x <- myXl$Wellname
  pattern = "(PSCO-)(?=0)" 
  
  values  <- grep(pattern, x, value = TRUE, perl = TRUE)
  indices <- grep(pattern, x, perl = TRUE)
  data.frame(indices, values, platform = myXl$Platform[indices])
#>   indices      values platform
#> 1      75 PSCO-027-TS        S
```

``` r
# replace the "I" by a blank
  x         <- myXl$Wellname
  pattern   <-  "(PSCO-)(?=0)"
  replaceBy <- paste0("\\1", myXl$Platform[[indices]])   # concatenate the platform
  
  myXl$Wellname[indices]  # before
#> [1] "PSCO-027-TS"
  myXl$Wellname[indices]  <- gsub(pattern, replaceBy, x[indices], perl = TRUE)
  myXl$Wellname[indices]  # after
#> [1] "PSCO-S027-TS"
```

Well names are done!

### Company

``` r

x        <- myXl$Company
patttern <- "Oil Gains Co."

grep(pattern, x, value = TRUE, perl = TRUE)
#> character(0)
# We don't get any return. All the company names are the same. Cool!
```

We don't get any return. All the company names are the same. Cool!

### Analyst

``` r
# summary(myXl$Analyst)
unique(myXl$Analyst)
#>  [1] "Aida"     "Ibironke" "Ibironk"  "Vivek"    "Americo"  "Norman"  
#>  [7] "Rod"      "Rodrigo"  "Sam"      "Thomas"   "Tom"      "Kai"     
#> [13] "Andrew"   "Andy"     "Camden"   NA
length(unique(myXl$Analyst))
#> [1] 16
```

``` r
operators <- c("Aida", "Americo", "Andrew", "Camden", "Ibironke", "Kai", "Norman", 
               "Rodrigo", "Sam", "Tom", "Vivek")

# find incorrect assignments
x <- myXl$Analyst
  indices <- which(!x %in% operators)
  result  <- myXl$Analyst[indices]
  data.frame(indices, result)
#>   indices  result
#> 1       9 Ibironk
#> 2      31     Rod
#> 3      32     Rod
#> 4      33     Rod
#> 5      37  Thomas
#> 6      78    Andy
#> 7      83    Andy
#> 8      98    <NA>
```

We can correct manually:

``` r
myXl$Analyst[9] <- "Ibironke"
myXl$Analyst[c(31,32,32,33)] = "Rodrigo"
myXl$Analyst[c(78,83)] = "Andrew"
myXl$Analyst[c(37)] = "Tom"

# verify if we have incorrect assignements
  myXl$Analyst[indices]
#> [1] "Ibironke" "Rodrigo"  "Rodrigo"  "Rodrigo"  "Tom"      "Andrew"  
#> [7] "Andrew"   NA
  indices <- which(!myXl$Analyst %in% operators)
  myXl$Analyst[indices]
#> [1] NA
```

There is only one observation left, the one with NA. We will have to cross-reference it. Let's find out who are the platform operators.

### Who is the platform operator?

In our particular case, who is the platform operator in "S"?

``` r
# Who is the platform operator?
  table(myXl$Analyst, myXl$Platform)
#>           
#>             M  Q  R  S
#>   Aida      6  0  1  0
#>   Americo   0  6  0  0
#>   Andrew    0  0  0 11
#>   Camden    0  0  0 14
#>   Ibironke  9  2  0  0
#>   Kai       0  0  8  0
#>   Norman    0  1  8  0
#>   Rodrigo   0  5  0  0
#>   Sam       0  1  0  0
#>   Tom       0  8  0  0
#>   Vivek     5  1 11  0
```

For platform S, it could be Andrew or Camden.

``` r
myXl[myXl$Analyst %in% c("Andrew", "Camden"), ]
#>        Wellname       Company Analyst Field Location Platform Fluid
#> 73 PSCO-S008-LS Oil Gains Co.  Andrew PISCO  S008-LS        S     0
#> 74 PSCO-S004-LS Oil Gains Co.  Andrew PISCO  S004-LS        S     0
#> 75 PSCO-S027-TS Oil Gains Co.  Andrew PISCO  S027-TS        S     0
#> 76 PSCO-S019-SS Oil Gains Co.  Andrew PISCO  S019-SS        S     0
#> 77 PSCO-S007-LS Oil Gains Co.  Andrew PISCO  S007-LS        S     0
#> 78 PSCO-S011-SS Oil Gains Co.  Andrew PISCO  S011-SS        S     0
#> 79 PSCO-S016-LS Oil Gains Co.  Andrew PISCO  S016-LS        S     0
#> 80 PSCO-S002-TS Oil Gains Co.  Andrew PISCO  S002-TS        S     0
#> 81 PSCO-S002-TS Oil Gains Co.  Andrew PISCO  S002-TS        S     0
#> 82 PSCO-S019-LS Oil Gains Co.  Andrew PISCO  S019-LS        S     0
#> 83 PSCO-S030-SS Oil Gains Co.  Andrew PISCO  S030-SS        S     0
#> 84 PSCO-S018-LS Oil Gains Co.  Camden PISCO  S018-LS        S     0
#> 85 PSCO-S026-SS Oil Gains Co.  Camden PISCO  S026-SS        S     0
#> 86 PSCO-S029-TS Oil Gains Co.  Camden PISCO  S029-TS        S     0
#> 87 PSCO-S018-SS Oil Gains Co.  Camden PISCO  S018-SS        S     0
#> 88 PSCO-S013-SS Oil Gains Co.  Camden PISCO  S013-SS        S     0
#> 89 PSCO-S015-LS Oil Gains Co.  Camden PISCO  S015-LS        S     0
#> 90 PSCO-S031-TS Oil Gains Co.  Camden PISCO  S031-TS        S     0
#> 91 PSCO-S032-SS Oil Gains Co.  Camden PISCO  S032-SS        S     0
#> 92 PSCO-S030-LS Oil Gains Co.  Camden PISCO  S030-LS        S     0
#> 93 PSCO-S032-LS Oil Gains Co.  Camden PISCO  S032-LS        S     0
#> 94 PSCO-S006-SS Oil Gains Co.  Camden PISCO  S006-SS        S     0
#> 95 PSCO-S021-TS Oil Gains Co.  Camden PISCO  S021-TS        S     0
#> 96 PSCO-S016-SS Oil Gains Co.  Camden PISCO  S016-SS        S     0
#> 97 PSCO-S015-SS Oil Gains Co.  Camden PISCO  S015-SS        S     0
#>    WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 73        0         1          0           0        3 455.183    36.1
#> 74        0         1          0           0        2 455.183    36.0
#> 75        0         1          1           3        7 455.183    36.1
#> 76        0         1          0           0        3 446.000    36.1
#> 77        0         1          0           0       10 455.183    36.1
#> 78        0         1          0           0        9 455.183    36.0
#> 79        0         1          0           0        3 455.183    36.1
#> 80        0         1          0           0        1 455.183    36.0
#> 81        0         1          0           0        1 455.183    36.0
#> 82        0         1          0           0        1 455.183    36.1
#> 83        0         1          1           3        8 439.000    36.0
#> 84        0         1          0           0        3 455.183    36.1
#> 85        0         1          0           0       10 455.183    36.1
#> 86        0         1          1           3        8 455.183    36.1
#> 87        0         1          0           0        6 450.747    36.0
#> 88        0         1          0           0        4 450.747    36.0
#> 89        0         1          0           0        3 455.183    36.8
#> 90        0         1          1           0        4 455.183    36.0
#> 91        0         1          0           3        6 450.747    36.0
#> 92        0         1          1           3        9 455.183    36.1
#> 93        0         1          0           3        4 455.183    36.1
#> 94        0         1          0           0        7 446.000    36.1
#> 95        0         1          0           0        9 455.183    36.1
#> 96        0         1          0           0        4 450.747    36.0
#> 97        0         1          0           0        3 450.747    36.1
#>    PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 73        1.3             10000       0   74.00           3             1
#> 74        1.3             15000       0   73.00           3             1
#> 75        1.3             10000       0   74.00           3             1
#> 76        1.2             10000       0   65.00           3             1
#> 77        1.3             10000       0   70.00           3             1
#> 78        1.3             15000       0   70.00           3             1
#> 79        1.3             15000       0   70.00           3             0
#> 80        1.3             15000       0   73.00           3             1
#> 81        1.3             15000       0   73.00           3             1
#> 82        1.3             10000       0   74.00           3             1
#> 83        1.3             15000       0   74.00           3             2
#> 84        1.3             15000       0   70.00           3             0
#> 85        1.3             10000       0   74.00           3             0
#> 86        1.3             10000       0   74.00           3             1
#> 87        1.3             10000       0   70.00           3             1
#> 88        1.3             10000       0   70.00           3             1
#> 89        1.3             30000       0   70.00           3             0
#> 90        1.3             15000       0   73.00           3             1
#> 91        1.3             10000       0   70.00           3             1
#> 92        1.3             15000       0   70.00           3             0
#> 93        1.3             10000       0   74.00           3             1
#> 94        1.3             10000       0   74.28           3             1
#> 95        1.3             10000       0   74.00           3             1
#> 96        1.3             10000       0   70.00           3             1
#> 97        1.3             30000       0   74.00           3             1
#>    PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 73  208.00006   1850.696       10        1    1574.696    208.0001
#> 74  208.00000   1836.000       10        1    1599.996    215.0006
#> 75  208.00000   1850.696       10        1    1695.700    217.9990
#> 76  206.00000   1808.696       10        1    1114.700    205.0000
#> 77  208.00000   1836.000       10        1    1560.000    226.0000
#> 78   97.77777   1836.000       10        1    1485.000    107.5780
#> 79  208.00000   1835.996       10        1    1513.700    223.0000
#> 80  208.00000   1836.000       10        0    1400.000    215.0010
#> 81  208.00000   1836.000       10        0    1400.000    215.0010
#> 82  208.00000   1850.696       10        1    1695.696    217.9994
#> 83  208.00000   1835.696       10        1    1480.750    206.0000
#> 84  208.00000   1821.304       10        1    1425.300    223.0000
#> 85  208.00006   1850.696       10        1    1591.696    208.0001
#> 86  208.00006   1850.696       10        1    1574.700    212.0000
#> 87  208.00000   1821.000       10        1    1479.996    206.0001
#> 88  208.00000   1821.000       10        0    1664.700    206.0000
#> 89  208.00000   1850.696       18        1    1564.700    208.0000
#> 90  208.00000   1836.000       10        1    1685.996    212.0000
#> 91  208.00000   1821.000       10        1    1591.696    206.0001
#> 92  208.00006   1835.996       10        1    1664.700    214.0000
#> 93  208.00006   1850.696       10        1    1622.700    208.0000
#> 94  206.00000   1808.696       18        1    1414.696    205.0000
#> 95  208.00000   1850.700       10        1    1664.696    208.0001
#> 96  208.00000   1821.000       10        1    1580.000    206.0000
#> 97  208.00006   1835.696       18        1    1494.700    208.0000
#>    IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES   IPR_PI   GEO_THMD
#> 73      500.0  85.00       330.0       743.749 0.800000 0|7273.62|
#> 74      720.0  19.00       763.6       656.284 0.580000  0|5856.3|
#> 75      700.0   2.00      1075.0       736.188 1.550000 0|5141.08|
#> 76     2674.0  60.00      1004.0       975.861 0.755000 0|6542.98|
#> 77      507.0  50.76       507.1       912.957 2.200000 0|5583.99|
#> 78      940.0  44.00       362.0       668.011 0.628750 0|9186.35|
#> 79      530.0  51.00       286.0       860.421 0.500000 0|4734.58|
#> 80      632.0  70.00         0.0         0.000 1.860078 0|5347.77|
#> 81      632.0  70.00         0.0         0.000 1.860078 0|5347.77|
#> 82      850.0  50.69      1082.2       589.100 1.400000 0|7372.05|
#> 83      500.0  17.00       396.0       715.239 0.700000 0|4757.22|
#> 84      530.0  62.00       317.8       658.660 0.400000 0|4558.07|
#> 85      658.0  62.00       200.0      1068.786 1.200000 0|9500.98|
#> 86      500.0  52.00       658.0       851.995 0.800000 0|8874.67|
#> 87      569.0  69.00       864.0      1021.896 2.000000 0|4503.94|
#> 88     1259.0  96.00         0.0         0.000 1.782440 0|4289.04|
#> 89      592.0  47.00       492.0       673.926 0.680000 0|6289.37|
#> 90      513.0  18.00       396.0       713.689 0.500000 0|6056.43|
#> 91     1000.0  69.00       250.0       692.188 0.800000 0|5521.65|
#> 92      500.0  71.00      2398.0      1381.096 9.000000 0|4652.23|
#> 93      500.0  71.00      1634.0      1053.136 3.050000 0|6089.24|
#> 94     1000.0  52.00       359.0       555.593 1.690000  0|6952.1|
#> 95     1500.0  75.00       100.0      1202.016 2.300000 0|13556.4|
#> 96      558.7  64.89      1664.0      1214.996 1.650000 0|4921.26|
#> 97     7737.0  52.00      1087.0       949.975 2.600000 0|6008.86|
#>          GEO_THTEMP GL_method
#> 73          80|204|         2
#> 74          80|208|         2
#> 75         104|218|         2
#> 76          80|203|         2
#> 77          80|226|         2
#> 78 26.6667|107.578|         2
#> 79          80|214|         2
#> 80          70|203|         2
#> 81          70|203|         2
#> 82     60.0001|206|         2
#> 83         140|206|         0
#> 84          60|223|         2
#> 85     122|208.004|         2
#> 86          87|212|         2
#> 87          60|219|         2
#> 88          70|204|         2
#> 89     60.0001|208|         2
#> 90          80|212|         2
#> 91      80|212.714|         2
#> 92         140|208|         2
#> 93          60|208|         2
#> 94          80|205|         2
#> 95          80|212|         2
#> 96     60.0001|214|         2
#> 97          80|199|         2
#>                                            GL_ArrayMandrels GL_Vdepth
#> 73       2514.44|4388.78|5730.31|6075.13|6955.05|0|0|0|0|0|     0.000
#> 74  2207.02|3490.49|4464.24|5214.9|5716.86|5773.62|0|0|0|0|  2207.021
#> 75        1532.15|2408.14|3133.2|3697.51|4501.31|0|0|0|0|0|  4501.310
#> 76                   4206.04|5738.19|6328.74|0|0|0|0|0|0|0|  4206.693
#> 77       2196.52|3480.97|3543.31|4484.91|4547.24|0|0|0|0|0|  5114.830
#> 78             2369.75|5120.08|7206.36|8852.03|0|0|0|0|0|0|  8852.034
#> 79         2144.36|3055.77|3747.7|4250.66|4564.3|0|0|0|0|0|  4250.656
#> 80                               5242.78|0|0|0|0|0|0|0|0|0|  5022.310
#> 81                               5242.78|0|0|0|0|0|0|0|0|0|  5022.310
#> 82                          2454.4|4285.43|0|0|0|0|0|0|0|0|  4284.780
#> 83 1332.02|2109.58|2752.62|3316.93|3792.65|4199.48|0|0|0|0|  4199.480
#> 84                   1751.97|3238.19|4219.49|0|0|0|0|0|0|0|  1286.100
#> 85                               4887.14|0|0|0|0|0|0|0|0|0|  4885.170
#> 86 1512.47|2746.06|3969.82|5193.57|6381.23|7542.65|0|0|0|0|  7542.651
#> 87                   1848.75|2578.41|4063.65|0|0|0|0|0|0|0|  4063.650
#> 88                         2734.91|3523.95|0|0|0|0|0|0|0|0|  3523.620
#> 89                   2432.09|4136.15|5459.97|0|0|0|0|0|0|0|  5774.278
#> 90 915.354|1702.76|2526.25|3382.55|4265.09|5167.32|0|0|0|0|  5167.323
#> 91                         2450.79|3415.35|0|0|0|0|0|0|0|0|  3415.354
#> 92             2309.71|2906.82|3467.85|3986.22|0|0|0|0|0|0|  4199.475
#> 93       1213.91|1981.63|2814.96|3963.25|5019.69|0|0|0|0|0|  5019.685
#> 94       2551.84|4426.18|5548.88|6420.93|6826.77|0|0|0|0|0|  6826.771
#> 95                   3113.19|5289.04|6867.78|0|0|0|0|0|0|0|  7939.305
#> 96       2106.63|3018.37|3710.96|4217.19|4532.48|0|0|0|0|0|  4530.840
#> 97                   2369.09|4073.16|5774.61|0|0|0|0|0|0|0|  5774.278
#>    GL_GSG GL_CO2
#> 73    1.2     65
#> 74    1.2     65
#> 75    1.2     65
#> 76    1.2     65
#> 77    1.2     65
#> 78    1.2     65
#> 79    1.2     65
#> 80    1.2     65
#> 81    1.2     65
#> 82    1.2     65
#> 83    1.2     65
#> 84    1.2     65
#> 85    1.2     65
#> 86    1.2     65
#> 87    1.2     65
#> 88    1.2     65
#> 89    1.2     65
#> 90    1.2     65
#> 91    1.2     65
#> 92    1.2     65
#> 93    1.2     65
#> 94    1.2     65
#> 95    1.2     65
#> 96    1.2     65
#> 97    1.2     65
#>                                                                                                           WT_DATE
#> 73                                                                              19/09/2014|17/01/2015|17/01/2015|
#> 74                                                                                         06/04/2014|31/12/2014|
#> 75                                  21/11/2013|15/04/2014|04/05/2014|12/06/2014|15/04/2014|15/01/2015|15/01/2015|
#> 76                                                                              06/06/2014|27/01/2015|27/01/2015|
#> 77 29/01/2013|12/02/2013|13/03/2013|25/09/2013|20/10/2013|11/03/2013|18/05/2014|16/07/2014|18/05/2914|02/01/2015|
#> 78                      |25/09/2013|19/07/2013|15/06/2014|15/06/2014|11/07/2014|12/05/2014|24/01/2015|24/01/2015|
#> 79                                                                                        |19/09/2014|19/09/2014|
#> 80                                                                                                           <NA>
#> 81                                                                                                           <NA>
#> 82                                                                                                          42005
#> 83                       08/08/2012|15/09/2012|09/10/2012|20/06/2012|30/07/2012|18/04/2014|21/05/2014|14/06/2014|
#> 84                                                                              05/01/2014|16/06/2014|23/12/2014|
#> 85           |22/09/2013|17/10/2013|18/04/2014|21/05/2014|10/06/2014|10/06/2014|13/07/2014|20/01/2015|20/01/2015|
#> 86                       24/09/2013|11/11/2013|08/03/2014|13/04/2014|16/06/2014|16/06/2014|16/07/2014|18/12/2014|
#> 87                                             19/03/2013|05/05/2014|07/07/2014|17/09/2014|18/01/2015|18/01/2015|
#> 88                                                                   31/10/2012|19/11/2012|29/01/2013|23/04/2013|
#> 89                                                                              14/06/2014|17/01/2015|17/01/2015|
#> 90                                                                   14/06/2014|21/05/2014|20/01/2015|20/01/2015|
#> 91                                             18/04/2014|09/07/2014|09/07/2014|24/02/2014|18/01/2015|18/01/2015|
#> 92            08/08/2012|15/09/2012|09/10/2012|20/06/2012|30/07/2012|21/05/2014|05/06/2014|05/06/2014|05/07/2014|
#> 93                                                                   14/04/2014|21/05/2014|10/06/2014|10/06/2014|
#> 94                                  19/02/2009|23/09/2013|10/04/2013|23/11/2013|07/03/2014|07/03/2014|18/12/2014|
#> 95                      |29/01/2013|01/03/2013|15/03/2013|21/07/2013|14/07/2014|31/08/2014|24/01/2015|24/01/2015|
#> 96                                                                             |16/06/2013|06/07/2014|17/01/2015|
#> 97                                                                              06/06/2014|06/06/2014|16/09/2014|
#>                                                    WT_THT
#> 73                                       104|186.8|102.2|
#> 74                                            87.8|116.6|
#> 75                       114.8|149|149|141|110|154.4|140|
#> 76                                          93|165.2|125|
#> 77 172.4|158|172.4|203|179.6|192.2|159.8|145.4|140|116.6|
#> 78                  30.5556|55|49|59|44|45|40.5556|41|42|
#> 79                                           87|176|98.6|
#> 80                                                    138
#> 81                                                    138
#> 82                                          109.400009155
#> 83           123.8|134.6|131|123.8|123.8|136.4|168.8|149|
#> 84                                           120|84|89.6|
#> 85   158|158|158|165.2|141.8|161.6|141.8|141.8|172.4|131|
#> 86                       52|69|68|73|152.6|116.6|167|122|
#> 87                   143.6|172.4|127.4|179.6|190.4|141.8|
#> 88                                 183.2|190.4|179.6|130|
#> 89                                        95|116.96|89.6|
#> 90                                       104|98.6|140|95|
#> 91                         185|172.4|122|87.5|190.4|98.6|
#> 92       123.8|134.6|131|123.8|123.8|145.4|194|183.2|194|
#> 93                                 190.4|158|181.4|136.4|
#> 94                   163.4|141.8|140|100|163.4|113|105.8|
#> 95          87.0001|145.4|145.4|149|156.2|104|104|0|84.2|
#> 96                               87.0001|179.6|125|147.2|
#> 97                                         185|133|188.6|
#>                                                       WT_LIQRT
#> 73                                                491|330|330|
#> 74                                                  397|763.6|
#> 75                        339|1261|687|1075|212|1159.1|1159.1|
#> 76                                            274.5|1004|1004|
#> 77 2469.36|821.16|1337.4|581|1208|689|4116|1093|1307.16|507.1|
#> 78                       1142|350|263|455|455|529|369|362|362|
#> 79                                               1142|286|286|
#> 80                                                        1142
#> 81                                                        1142
#> 82                                              1082.199951172
#> 83                  284.1|150.6|231.6|69.84|69.84|279|195|396|
#> 84                                              847|270|317.8|
#> 85                  770|1500|1400|137|387|613|613|711|200|200|
#> 86                            656|880|953|484|658|658|353|556|
#> 87                         594.72|1037.9|864|1261.9|1143|1143|
#> 88                                           505|755|2418|859|
#> 89                                            492|383.2|383.2|
#> 90                                            396|243|267|267|
#> 91                                    326|650|650|439|250|250|
#> 92          284.1|150.6|231.6|69.84|69.84|2365|2398|2398|2166|
#> 93                                        1975|1413|1634|1634|
#> 94                               1518|951|543|515|814|814|359|
#> 95                    1142|882|674.52|615|611|672|889|100|100|
#> 96                                      1142|1482|1021.3|1664|
#> 97                                           1087|1087|1353.8|
#>                                  WT_WC
#> 73                           85|85|85|
#> 74                            5|18.83|
#> 75               2|0.9|14|0|2|4.9|4.9|
#> 76                           20|60|60|
#> 77 86.7|75|80|75|73|82|92|56|54|50.76|
#> 78         89|55|50|60|60|23|59|44|44|
#> 79                           89|51|51|
#> 80                                  89
#> 81                                  89
#> 82                        50.689998627
#> 83                 0|0|0|0|0|19|20|17|
#> 84                           64|62|62|
#> 85      75|90|90|63|41|63|63|51|62|62|
#> 86            70|20|64|54|52|52|44|54|
#> 87         69.14|61.73|69|77.12|78|78|
#> 88                        88|91|85|96|
#> 89                     47|63.51|63.51|
#> 90                        17|20|18|18|
#> 91                  61|66|66|38|69|69|
#> 92              0|0|0|0|0|74|71|71|70|
#> 93                        40|69|71|71|
#> 94               65|60|60|68|60|60|52|
#> 95      89|60|60|93.92|70|57|75|75|75|
#> 96                  89|72|52.13|64.89|
#> 97                        52|52|50.77|
#>                                                                  WT_THP
#> 73                                             327.696|245.696|245.696|
#> 74                                                          100|80.696|
#> 75             173.696|214.696|188.696|246.696|269.696|217.696|217.696|
#> 76                                               174.696|429.396|417.5|
#> 77               261.138|261.138|275.641|232|203|232|203|305|232|195.7|
#> 78                      159.304|261|232|174|174|208|143.67|265.2|265.2|
#> 79                                                 174|119.696|119.696|
#> 80                                                        174.000000854
#> 81                                                        174.000000854
#> 82                                                        122.395996948
#> 83          174.24|156.84|159.74|174.24|174.24|213.346|171.839|246.696|
#> 84                                               194.304|188.304|195.6|
#> 85 174|261|275|246.696|228.696|217.696|217.696|207.696|304.696|304.696|
#> 86     275.696|231.696|377.696|203.696|231.696|231.696|231.696|281.696|
#> 87                                 217.798|193|249|174|246.696|246.696|
#> 88                                                     159|130|246|203|
#> 89                                             217.696|217.596|217.596|
#> 90                                             232|160|232.196|232.196|
#> 91                     214.696|191.696|191.696|152.696|246.696|246.696|
#> 92  174.24|156.84|159.74|174.24|174.24|275.696|289.696|289.696|246.696|
#> 93                                     214.696|275.696|173.696|173.696|
#> 94             289.696|318.696|449.696|304.696|285.696|285.696|303.296|
#> 95     174|319.355|319.355|275.834|218|203.696|239.446|259.196|259.196|
#> 96                                                 174|218|203|250.896|
#> 97                                             333.696|333.696|275.696|
#>                                                     WT_GOR
#> 73                                            500|500|500|
#> 74                                                720|720|
#> 75                           2626|586|950|700|500|660|500|
#> 76                                         1000|2674|2674|
#> 77 1921.27|2925.87|3098.74|388|1123|2034|2801|934|455|530|
#> 78               9001|3129|2827|2635|611|364|550|6247|940|
#> 79                                           9001|540|530|
#> 80                                                    9001
#> 81                                                    9001
#> 82                                                     850
#> 83           2625|2958|2625|3217.56|3378.56|860|14012|500|
#> 84                                            450|530|530|
#> 85            820|5200|5200|873|305|1080|505|1080|658|658|
#> 86                     1050|1800|837|112|159|500|5056|667|
#> 87                             802.84|530|567|530|537|573|
#> 88                                    1259|1261|1260|1259|
#> 89                                         592|1007.7|970|
#> 90                                     522|1694|802.8|520|
#> 91                             953|6687|957|700|5654|1119|
#> 92        2625|2958|2625|3217.56|3378.56|1251|342|500|201|
#> 93                                       342|2744|952|500|
#> 94                       1680|1680|3691|550|2396|500|1000|
#> 95     9001|2100.91|2100.84|2249|2100|887|1390|20616|1780|
#> 96                                    9001|2573|500|558.7|
#> 97                                           749|773|1000|
#>                                                WT_GLIR
#> 73                                     0.46|0.38|0.38|
#> 74                                         0.125|0.15|
#> 75                  0.04|0.6|0.56|0.75|0.06|0.48|0.35|
#> 76                                       0.15|0.3|0.2|
#> 77                     0|0|0|0.27|0|0|0|0.23|0.1|0.36|
#> 78                  0.1|0.3|0.3|0|0.1|1|0.1|0.33|0.33|
#> 79                                     0.1|0.015|0.02|
#> 80                                         0.100000001
#> 81                                         0.100000001
#> 82                                         0.280000001
#> 83             0.096|0.047|0|0.05|0.05|0.96|0.47|0.17|
#> 84                                   0.162|0.38|0.185|
#> 85   0.165|0.3|0.3|0.12|0.34|0.34|0.34|0.39|0.55|0.55|
#> 86            0.47|0.7|0.3|0.98|0.67|0.375|0.56|0.325|
#> 87                    0.33902|0.14|0.18|0.26|0.41|0.6|
#> 88                               0.033|0|0.2161|0.339|
#> 89                                  0.3|0.1075|0.1075|
#> 90                                   0.6|0.47|0.3|0.1|
#> 91                       0.24|0.47|0.47|0.1|0.205|0.2|
#> 92        0.096|0.047|0|0.05|0.05|0.43|0.24|0.29|0.11|
#> 93                                    0.98|0.5|0|0.29|
#> 94                    0|0.635|0.158|0.343|1|0.5|0.535|
#> 95 0.1|0.29664|0.295|0.29664|0.15|0.14|0.15|0.33|0.33|
#> 96                                  0.1|0.128|0.5|0.3|
#> 97                                      0.48|0.48|0.5|
#>                                                                            WT_DEPTH
#> 73                                                         6955.05|6955.05|6955.05|
#> 74                                                                 5773.62|5773.62|
#> 75                         4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|
#> 76                                                         6328.74|6328.74|6328.74|
#> 77                   0|0|0|5114.83|5114.83|5115.81|5115.81|5115.81|4547.24|4547.24|
#> 78         4548.88|8851.71|8851.71|8851.71|5120.08|8851.71|2040.68|2040.68|2040.68|
#> 79                                                           4548.88|3747.7|3747.7|
#> 80                                                                   4548.884277344
#> 81                                                                   4548.884277344
#> 82                                                                   4285.433105469
#> 83                 4199.48|4199.48|4199.48|4199.48|4199.48|4199.48|4199.48|4199.48|
#> 84                                                         2637.47|2637.47|2637.47|
#> 85 4887.11|4887.11|4887.11|4887.11|4887.11|4887.11|4887.11|4887.11|4887.11|4887.11|
#> 86                 7542.65|7542.65|7542.65|7542.65|7542.65|7542.65|7542.65|7542.65|
#> 87                                 4063.65|4063.65|4063.65|4063.65|4063.65|4063.65|
#> 88                                                 4061.35|4061.35|4061.35|4061.35|
#> 89                                                         5459.97|5459.97|5459.97|
#> 90                                                 5167.32|5167.32|5167.32|5167.32|
#> 91                                 3415.35|3415.35|3415.35|3415.35|3415.35|3415.35|
#> 92         4199.48|4199.48|4199.48|4199.48|4199.48|3986.22|3986.22|3986.22|3986.22|
#> 93                                                 5019.69|5019.69|5019.69|5019.69|
#> 94                            6420.6|6420.6|6420.6|6826.77|6826.77|6826.77|6826.77|
#> 95             4548.88|7939.3|7939.3|7939.3|6866.8|6867.78|6867.78|6867.78|6867.78|
#> 96                                                 4548.88|4547.24|4532.48|4532.48|
#> 97                                                         5774.61|5774.61|5774.61|
#>               WT_Enable
#> 73               1|1|0|
#> 74                 1|0|
#> 75       1|1|1|1|1|1|0|
#> 76               1|1|0|
#> 77 1|1|1|1|1|1|1|1|1|0|
#> 78   1|1|1|1|1|1|1|1|0|
#> 79               1|1|0|
#> 80                    0
#> 81                    0
#> 82                    0
#> 83     1|1|1|1|1|1|1|0|
#> 84               1|1|0|
#> 85 1|1|1|1|1|1|1|1|1|0|
#> 86     1|1|1|1|1|1|1|0|
#> 87         1|1|1|1|1|0|
#> 88             1|1|1|0|
#> 89               1|1|0|
#> 90             1|1|1|0|
#> 91         1|1|1|1|1|0|
#> 92   1|1|1|1|1|1|1|0|1|
#> 93             1|1|1|0|
#> 94       1|1|1|1|1|1|0|
#> 95   1|1|1|1|1|1|1|1|0|
#> 96             1|1|1|0|
#> 97               1|0|1|
#>                                                       WT_GDEPTH
#> 73                                           7273.62|0|7273.62|
#> 74                                               5856.3|5856.3|
#> 75                             0|0|0|5141.08|5141.08|0|5141.08|
#> 76                                                 6542.98|0|0|
#> 77     4625.92|4625.92|4625.92|0|0|0|0|5515.09|5561.02|5561.02|
#> 78                   0|0|0|9186.35|9186.35|0|9186.35|0|9186.35|
#> 79                                                 0|0|4734.58|
#> 80                                                            0
#> 81                                                            0
#> 82                                               7372.047363281
#> 83                                             0|0|0|0|0|0|0|0|
#> 84                                     4558.07|4558.07|4558.07|
#> 85                       9484.91|0|0|0|0|0|9500.98|9500.98|0|0|
#> 86                                 0|0|0|0|0|8874.67|0|8874.67|
#> 87                               4454.66|0|4419.29|0|0|4419.29|
#> 88                                                     0|0|0|0|
#> 89                                           6279.53|0|6279.53|
#> 90                                   6056.43|6056.43|0|6056.43|
#> 91                               0|0|5521.65|5521.65|0|5521.65|
#> 92                                     0|0|0|0|0|0|0|4652.23|0|
#> 93                                               0|0|0|6089.24|
#> 94                                0|0|0|7029.2|0|6952.1|6952.1|
#> 95 0|13517.7|13517.7|13517.7|13556.4|13556.4|13556.4|0|13556.4|
#> 96                                   0|4665.35|4666.34|4666.34|
#> 97                                                 0|6008.86|0|
#>                                                                WT_GPRES
#> 73                                             917.006|245.696|743.749|
#> 74                                                     574.078|656.284|
#> 75             173.696|214.696|188.696|736.188|738.696|217.696|584.258|
#> 76                                                 531.484|414.7|417.5|
#> 77      1341.03|826.728|948.84|232|203|232|203|1014.36|1443.22|912.957|
#> 78           159.304|261|232|1009.48|1159.51|208|1226.67|265.2|668.011|
#> 79                                                 174|119.696|860.421|
#> 80                                                        174.000000854
#> 81                                                        174.000000854
#> 82                                                        589.099991699
#> 83          174.24|156.84|159.74|174.24|174.24|213.696|171.696|246.696|
#> 84                                              1019.74|395.954|658.66|
#> 85 803|261|275|246.696|228.696|217.696|984.244|746.289|304.696|304.696|
#> 86     275.696|231.696|377.696|203.696|231.696|851.995|231.696|971.935|
#> 87                              795.52|193|1241.83|174|246.696|1086.17|
#> 88                                                     159|130|246|203|
#> 89                                             673.926|217.596|977.482|
#> 90                                         698.993|890|232.196|1364.11|
#> 91                     214.696|191.696|711.191|570.416|246.696|692.188|
#> 92   174.24|156.84|159.74|174.24|174.24|275.696|290.196|1381.1|246.696|
#> 93                                     174.696|275.696|173.696|1053.14|
#> 94             289.696|318.696|449.696|932.635|286.096|820.055|555.593|
#> 95      174|1096.92|1007.6|1285.93|867|1061.02|1246.47|259.196|1202.02|
#> 96                                                174|956|872.757|1215|
#> 97                                              333.696|949.975|14.696|
#>                                                           WT_RESPRES
#> 73                                             1574.7|1574.7|1574.7|
#> 74                                                        1600|1600|
#> 75                 1714.7|1698.7|1695.7|1695.7|1695.7|1695.7|1695.7|
#> 76                                            949.696|1114.7|1114.7|
#> 77          2929.3|2929.3|2929.3|1550|1550|1550|1550|1560|1560|1560|
#> 78              1499.3|1485.3|1276.52|1485|1485|1485|1485|1485|1485|
#> 79                                               1514|1513.7|1513.7|
#> 80                                                    1513.999955078
#> 81                                                    1513.999955078
#> 82                                                          1695.696
#> 83                 1500|1500|1500|1500|1500|1480.74|1480.74|1480.74|
#> 84                                             1425.3|1425.3|1425.3|
#> 85  1514|1400|1400|1399.7|1591.7|1591.7|1591.7|1591.7|1591.7|1591.7|
#> 86          1514.7|1514.7|1574.7|1574.7|1574.7|1574.7|1574.7|1574.7|
#> 87                                 969.233|1480|1480|1480|1480|1480|
#> 88                                              1400|1400|1400|1400|
#> 89                                             1564.7|1564.7|1564.7|
#> 90                                              1686|1686|1686|1686|
#> 91                        1591.7|1591.7|1591.7|1591.7|1591.7|1591.7|
#> 92             1500|1500|1500|1500|1500|1664.7|1664.7|1664.7|1664.7|
#> 93                                      1638.7|1638.7|1622.7|1622.7|
#> 94              1225.77|1225.77|1225.77|1414.7|1414.7|1414.7|1414.7|
#> 95 1513.99|1465.67|1465.67|1465.67|1465|1664.7|1664.7|1664.7|1664.7|
#> 96                                              1514|1514|1580|1580|
#> 97                                             1494.7|1494.7|1494.7|
#>                                       ProsperFilename
#> 73 \\\\network\\piscis\\well_models\\PISC-S008-LS.Out
#> 74 \\\\network\\piscis\\well_models\\PISC-S004-LS.Out
#> 75    \\\\network\\piscis\\well_models\\PISC-S027.Out
#> 76 \\\\network\\piscis\\well_models\\PISC-S019-SS.Out
#> 77 \\\\network\\piscis\\well_models\\PISC-S007-LS.Out
#> 78 \\\\network\\piscis\\well_models\\PISC-S011-SS.Out
#> 79 \\\\network\\piscis\\well_models\\PISC-S016-LS.Out
#> 80 \\\\network\\piscis\\well_models\\PISC-S002-TS.out
#> 81     \\\\network\\piscis\\well_models\\PISCS002.out
#> 82 \\\\network\\piscis\\well_models\\PISC-S019-LS.Out
#> 83 \\\\network\\piscis\\well_models\\PISC-S030-SS.Out
#> 84 \\\\network\\piscis\\well_models\\PISC-S018-LS.Out
#> 85 \\\\network\\piscis\\well_models\\PISC-S026-SS.Out
#> 86    \\\\network\\piscis\\well_models\\PISC-S029.Out
#> 87 \\\\network\\piscis\\well_models\\PISC-S018-SS.Out
#> 88 \\\\network\\piscis\\well_models\\PISC-S013-SS.Out
#> 89 \\\\network\\piscis\\well_models\\PISC-S015-LS.Out
#> 90    \\\\network\\piscis\\well_models\\PISC-S031.Out
#> 91 \\\\network\\piscis\\well_models\\PISC-S032-SS.Out
#> 92 \\\\network\\piscis\\well_models\\PISC-S030-LS.Out
#> 93 \\\\network\\piscis\\well_models\\PISC-S032-LS.Out
#> 94 \\\\network\\piscis\\well_models\\PISC-S006-SS.Out
#> 95    \\\\network\\piscis\\well_models\\PISC-S021.Out
#> 96 \\\\network\\piscis\\well_models\\PISC-S016-SS.Out
#> 97 \\\\network\\piscis\\well_models\\PISC-S015-SS.Out
```

There is not a real pattern here. We will assign the well to Andrew, make a note. Then we make a call to confirm.

``` r
myXl$Analyst[c(98)] = "Andrew"

# verify if we have incorrect assignements
  tocorrectIndices <- which(!myXl$Analyst %in% operators)
  myXl[tocorrectIndices, ]
#>  [1] Wellname          Company           Analyst          
#>  [4] Field             Location          Platform         
#>  [7] Fluid             WellType          AL_Method        
#> [10] Completion        SandControl       WT_COUNT         
#> [13] PVT_GOR           PVT_API           PVT_SG_gas       
#> [16] PVT_WaterSalinity PVT_H2S           PVT_CO2          
#> [19] PVT_PB_CORR       PVT_VISC_CORR     PVT_BPTEMP       
#> [22] PVT_BPPRES        VLP_CORR          IPR_CORR         
#> [25] IPR_RESPRES       IPR_RESTEMP       IPR_TOTGOR       
#> [28] IPR_WC            IPR_VOGELRT       IPR_VOGELPRES    
#> [31] IPR_PI            GEO_THMD          GEO_THTEMP       
#> [34] GL_method         GL_ArrayMandrels  GL_Vdepth        
#> [37] GL_GSG            GL_CO2            WT_DATE          
#> [40] WT_THT            WT_LIQRT          WT_WC            
#> [43] WT_THP            WT_GOR            WT_GLIR          
#> [46] WT_DEPTH          WT_Enable         WT_GDEPTH        
#> [49] WT_GPRES          WT_RESPRES        ProsperFilename  
#> <0 rows> (or 0-length row.names)

  # Analyst is complete  
```

Check the field
---------------

``` r
unique(myXl$Field)
#> [1] "PISCO" NA      "pisco"
# we have two additional keywords for the field that have to be corrected.
# let's find out what indices they have
```

``` r
# verify for bad names in field
indices <- grep("[^PISCO]", myXl$Field)      # which means those which are not named like PISCO
result <-  grep("[^PISCO]", myXl$Field, value = TRUE)
df1 <- data.frame(indices, result)
df1
#>   indices result
#> 1      12  pisco
#> 2      27  pisco
```

``` r
# which row index has NAs in it
indices  <- which(is.na(myXl$Field))
result   <- myXl$Field[indices]
df2      <- data.frame(indices, result)
df2
#>   indices result
#> 1       7   <NA>
```

``` r
# combine both data frames
rbind(df1, df2)
#>   indices result
#> 1      12  pisco
#> 2      27  pisco
#> 3       7   <NA>
```

``` r
# make the correction
myXl$Field[c(7,12,27)] <- "PISCO"

# verify for bad names in field
  grep("[^PISCO]", myXl$Field)    # which means those which are not named like PISCO
#> integer(0)
  
# which row index has NAs in it
  which(is.na(myXl$Field))
#> integer(0)
  
# it has been fixed now  
```

Add a column for the Completion Type
------------------------------------

To close this chapter, let's add a c new variable (column) where we have only the Completion Type. We can take advantage that the last two characters of the well name is the completion type.

    nchar(): number of character of the string

``` r
substr(myXl$Wellname, nchar(myXl$Wellname)-1, nchar(myXl$Wellname))
#>   [1] "TS" "TS" "LS" "TS" "SS" "TS" "LS" "LS" "LS" "LS" "SS" "SS" "SS" "LS"
#>  [15] "TS" "LS" "SS" "SS" "LS" "TS" "LS" "SS" "SS" "SS" "SS" "LS" "LS" "SS"
#>  [29] "SS" "LS" "SS" "LS" "SS" "LS" "LS" "TS" "LS" "LS" "SS" "LS" "SS" "SS"
#>  [43] "SS" "TS" "SS" "LS" "SS" "LS" "SS" "TS" "LS" "SS" "SS" "LS" "SS" "SS"
#>  [57] "LS" "SS" "TS" "SS" "LS" "LS" "SS" "SS" "TS" "LS" "SS" "SS" "TS" "SS"
#>  [71] "LS" "SS" "LS" "LS" "TS" "SS" "LS" "SS" "LS" "TS" "TS" "LS" "SS" "LS"
#>  [85] "SS" "TS" "SS" "SS" "LS" "TS" "SS" "LS" "LS" "SS" "TS" "SS" "SS" "LS"
#>  [99] "TS" "TS"
```

``` r
# assign the completion type to a new column
myXl$Completion <- substr(myXl$Wellname, nchar(myXl$Wellname)-1, nchar(myXl$Wellname))
myXl$Completion
#>   [1] "TS" "TS" "LS" "TS" "SS" "TS" "LS" "LS" "LS" "LS" "SS" "SS" "SS" "LS"
#>  [15] "TS" "LS" "SS" "SS" "LS" "TS" "LS" "SS" "SS" "SS" "SS" "LS" "LS" "SS"
#>  [29] "SS" "LS" "SS" "LS" "SS" "LS" "LS" "TS" "LS" "LS" "SS" "LS" "SS" "SS"
#>  [43] "SS" "TS" "SS" "LS" "SS" "LS" "SS" "TS" "LS" "SS" "SS" "LS" "SS" "SS"
#>  [57] "LS" "SS" "TS" "SS" "LS" "LS" "SS" "SS" "TS" "LS" "SS" "SS" "TS" "SS"
#>  [71] "LS" "SS" "LS" "LS" "TS" "SS" "LS" "SS" "LS" "TS" "TS" "LS" "SS" "LS"
#>  [85] "SS" "TS" "SS" "SS" "LS" "TS" "SS" "LS" "LS" "SS" "TS" "SS" "SS" "LS"
#>  [99] "TS" "TS"
```

Location
--------

``` r
myXl$Location
#>   [1] "M005-TS" "M007-TS" "M004-LS" "M008-TS" "M010-SS" "M006-TS" "M016-LS"
#>   [8] "M018-LS" "M021-LS" "M017-LS" "M030-SS" "M027-SS" "M016-SS" "M020-LS"
#>  [15] "M028-TS" "M015-LS" "M018-SS" "M015-SS" NA        "M012-TS" "Q007-LS"
#>  [22] "Q001-SS" "Q005-SS" "Q011-SS" "Q002-SS" "Q002-LS" "Q003-LS" "Q004-SS"
#>  [29] "Q009-SS" "Q019-LS" "Q032-SS" "Q028-LS" "Q028-SS" "Q029-LS" "Q032-LS"
#>  [36] "Q024-TS" "Q018-LS" "Q017-LS" "Q013-SS" "Q014-LS" "Q017-SS" "Q014-SS"
#>  [43] "Q018-SS" "Q012-TS" "R009-SS" "R015-LS" "R019-SS" "R019-LS" "R020-SS"
#>  [50] "R013-TS" "R012-LS" "R012-SS" "R018-SS" "R018-LS" "R015-SS" "R020-SS"
#>  [57] "R004-LS" "R001-SS" "R003-TS" "R006-SS" "R007-LS" "R001-LS" "R007-SS"
#>  [64] "R002-SS" "R029-TS" "R027-LS" "R025-SS" "R023-SS" "R022-TS" "R021-SS"
#>  [71] "R023-LS" "R027-SS" "S008-LS" "S004-LS" "S027-TS" "S019-SS" "S007-LS"
#>  [78] "S011-SS" "S016-LS" "S002-TS" "S002-TS" "S019-LS" "S030-SS" "S018-LS"
#>  [85] "S026-SS" "S029-TS" "S018-SS" "S013-SS" "S015-LS" "S031-TS" "S032-SS"
#>  [92] "S030-LS" "S032-LS" "S006-SS" "S021-TS" "S016-SS" "S015-SS" "S012-LS"
#>  [99] "M001-TS" "M026-TS"
```

``` r
# we can test it by not following pattern or those which are NA
pattern <- "[MQRS][0-9]{3}"

# test that Location follows the pattern
indices <- grep(pattern, myXl$Location, invert = TRUE)
myXl$Location[indices]
#> [1] NA

data.frame(indices, myXl$Wellname[indices], myXl$Location[indices])
#>   indices myXl.Wellname.indices. myXl.Location.indices.
#> 1      19           PSCO-M002-LS                   <NA>
# there is one non-compliant index 
# which matches what we see above
```

``` r
myXl$Location[indices]  # before
#> [1] NA
myXl$Location[indices] <- substr(myXl$Wellname[indices], 
                                 nchar(myXl$Wellname[indices])-6, 
                                 nchar(myXl$Wellname[indices]))
myXl$Location[indices]  # after
#> [1] "M002-LS"
```

``` r
myXl$Location
#>   [1] "M005-TS" "M007-TS" "M004-LS" "M008-TS" "M010-SS" "M006-TS" "M016-LS"
#>   [8] "M018-LS" "M021-LS" "M017-LS" "M030-SS" "M027-SS" "M016-SS" "M020-LS"
#>  [15] "M028-TS" "M015-LS" "M018-SS" "M015-SS" "M002-LS" "M012-TS" "Q007-LS"
#>  [22] "Q001-SS" "Q005-SS" "Q011-SS" "Q002-SS" "Q002-LS" "Q003-LS" "Q004-SS"
#>  [29] "Q009-SS" "Q019-LS" "Q032-SS" "Q028-LS" "Q028-SS" "Q029-LS" "Q032-LS"
#>  [36] "Q024-TS" "Q018-LS" "Q017-LS" "Q013-SS" "Q014-LS" "Q017-SS" "Q014-SS"
#>  [43] "Q018-SS" "Q012-TS" "R009-SS" "R015-LS" "R019-SS" "R019-LS" "R020-SS"
#>  [50] "R013-TS" "R012-LS" "R012-SS" "R018-SS" "R018-LS" "R015-SS" "R020-SS"
#>  [57] "R004-LS" "R001-SS" "R003-TS" "R006-SS" "R007-LS" "R001-LS" "R007-SS"
#>  [64] "R002-SS" "R029-TS" "R027-LS" "R025-SS" "R023-SS" "R022-TS" "R021-SS"
#>  [71] "R023-LS" "R027-SS" "S008-LS" "S004-LS" "S027-TS" "S019-SS" "S007-LS"
#>  [78] "S011-SS" "S016-LS" "S002-TS" "S002-TS" "S019-LS" "S030-SS" "S018-LS"
#>  [85] "S026-SS" "S029-TS" "S018-SS" "S013-SS" "S015-LS" "S031-TS" "S032-SS"
#>  [92] "S030-LS" "S032-LS" "S006-SS" "S021-TS" "S016-SS" "S015-SS" "S012-LS"
#>  [99] "M001-TS" "M026-TS"
```

``` r
# test that Location follows the pattern
grep(pattern, myXl$Location, invert = TRUE)
#> integer(0)
# we are done here
```

Platform
--------

``` r
# verify which indices do not comply for platform
x <- myXl$Platform
pattern <- "[MQRS]"

indices <- grep(pattern, x, invert = TRUE)
values  <- grep(pattern, x, invert = TRUE, value = TRUE)
data.frame(indices, values, myXl$Wellname[indices])
#>   indices values myXl.Wellname.indices.
#> 1      99   <NA>           PSCO-M001-TS
#> 2     100   <NA>           PSCO-M026-TS
# only two not following
# since the well name is already corrected, let's use it
```

``` r
# extract the platform from the well name
myXl$Platform <- substr(myXl$Wellname, nchar(myXl$Wellname)-6, nchar(myXl$Wellname)-6)

# verify which indices do not comply for platform
grep("[MQRS]", myXl$Platform, invert = TRUE)
#> integer(0)
# we are done here
```
