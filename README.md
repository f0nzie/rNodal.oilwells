
<!-- README.md is generated from README.Rmd. Please edit that file -->
rNodal.oilwells
===============

The goal of `rNodal.oilwells` is to start processing well raw data and transforming it into tidy data.

Installation
------------

You can install rNodal.oilwells from github with:

``` r
# install.packages("devtools")
devtools::install_github("f0nzie/rNodal.oilwells")
```

Soon to be presented to CRAN.

Data Science for Petroleum Engineering - Part 5: "Transforming Excel well raw data into datasets.
=================================================================================================

One of the big challenges of this new era of data science. machine learning and artificial intelligence is getting unhooked from the habit of working with spreadsheets. They have been around for 30+ years and were awesome. But spreadsheets - or worksheets - do not scale well with massive amounts of data; or continuous streams of data; or other characteristics that are key for taking good and sound decisions such as **reproducibility**. Besides, spreadsheets have not kept with the times so we have seen the plotting capabilities getting very much behind of other software.

*Plots are the most expressive way that you can show your data and analysis.*

This time we will start with some well raw data. This data is part of the input data that we require to create well models for nodal analysis, IPR/VLP calibration with well test data, troubleshooting, plan a stimulation job, or reviewing the well technical potential. In my case, this data was input for Petroleum Experts's **Prosper**. But the same could have been used with Schlumberger's **Pipesim**, or any other.

Again, we will use R for these tasks. What we will do is:

-   Read the Excel data into R
-   Perform a basic statistics on the raw data
-   Find problems with data: data missing or improperly entered
-   Deal with missing data and correct typing issues
-   Convert the raw data to tidy data before analysis and plotting
-   Save the tidy data
-   See what story the data is trying to tell us
-   Present our discoveries

Setting the stage
-----------------

In order for you to be able to reproduce this analysis, you will need to install R, Rtools and RStudio. They are very easy to install. And the best of all, they are free.

Don't be mistaken. This is high quality software that will lead you to a world full of discoveries. So, I am assuming that at least you have installed R and that you already have your RStudio screen in front of you. This is supposed to be a sort of introductory session to R, so, I am assuming that you have little or no previous experience with R either. If you are an experienced user, you will skip to the end very quick.

Remember, R has been designed by scientists for the use of scientists and engineers. It is not only a tool for discovery but for development. I showed a little bit of it with the article on the [compressibility factor](https://www.linkedin.com/pulse/building-your-own-petroleum-engineering-library-r-humble-reyes).

The Raw Data
------------

We will start by reading the raw data. Raw data is data as-is. It hasn't been cleaned up or checked or organized. Although this raw data has had some treatment to allow us focus on the main goal. You will have access to the raw data via GitHub. I will publish all the material there: raw data, datasets, scripts, notebooks, etc. I may even publish a R package to make the installation much easier for you.

The raw is about input data for 100 wells. The input data is the minimum required to create a well model under any nodal analysis software. The well data could be grouped as: general data (well name, field, platform), well type data (fluid, completion type, artificial lift method), PVT data, IPR data, VLP data, geothermal data, gas lift data (for those wells that have artificial lift), and well test data.

**General data**

<img src="https://media.licdn.com/mpr/mpr/AAEAAQAAAAAAAAyfAAAAJDk5ZWYxMjRmLTA1NzctNDZmNy05YmMzLWI4MzMwMTA3NGFiMQ.jpg" width="500px" />

**Well type data**

<img src="https://media.licdn.com/mpr/mpr/AAEAAQAAAAAAAA2qAAAAJDkxN2Y5OTA3LWJiNWQtNDE3Yy04NTgxLTBlYjhhNGZkMzNkZA.jpg" width="500px" />

\*\*PVT <data:**>

<img src="https://media.licdn.com/mpr/mpr/AAEAAQAAAAAAAAo-AAAAJDgxZmIyOTVhLTU0OTgtNGIzNy04Y2JlLTJjODJhOWU3ZDcxYQ.jpg" width="600px" />

\*\* IPR data: \*\*

<img src="https://media.licdn.com/mpr/mpr/AAEAAQAAAAAAAAqNAAAAJDljYjEyM2IxLWVhYzgtNDYyMi04ZmYyLWQ4MjIxNmNkMWQ0ZQ.jpg" width="500px" />

\*\*Well test <data:**>

<img src="https://media.licdn.com/mpr/mpr/AAEAAQAAAAAAAAmwAAAAJDkyNjVmZWE1LWI1MzYtNGM4OC04NWNjLWY1YWY0OTUxNjdiYg.jpg" width="800px" />

The well test data transformation into tidy data will be a major task but that's life. That's how raw data comes. And then we use tools like R for the data munging. It will be fun.

Reading the raw data
--------------------

Now, back to our RStudio screen. R can read virtually any data format out there. If you just installed R and haven't installed anything else what you have is r-base. You can do a lot of stuff with it. But you wouldn't able to read an Excel spreadsheet. You have to install a package for that. The packages are supplements to the base R. If you need some specific type of plot or a statistical distribution that you didn't find in r-base you just install the package. There are 11,000+ of them. They can also be installed directly from the internet. We will start by installing the package xlsx which will allow us to read Excel .xlsx files.

``` r
install.packages("xlsx")
```

Once the package is installed we proceed to read the raw data:

``` r
# load the library xlsx
library(xlsx)
#> Loading required package: rJava
#> Loading required package: xlsxjars

# read the raw data
myXl <- read.xlsx("./inst/extdata/oilfield_100w_raw_data.xlsx", 
                  sheetIndex = 1, stringsAsFactors=FALSE)
```

I placed the raw data file under the directory ./inst/extdata, that why the long path. In R packages is very usual to place the raw data under this folder.

The first part of the command we see myXl, which is an object that will be holding whatever the data is inside the file. read.xlsx is the function that reads the Excel file. Then comes the long string "./inst/extdata/oilfield\_100w\_raw\_data.xlsx", then a comma and a number "1" that means the sheet number.

After you run this command take a look the top right side of your screen. Specifically, the Environment tab. You will see that the object myXl is showing this:

<img src="https://media.licdn.com/mpr/mpr/AAEAAQAAAAAAAAxtAAAAJGE3NGVmZDQ5LWY4ZDYtNDExNy04YzE3LTFmMDk0YmZjMTcxNQ.jpg" width="500px" />

That means 100 **observations** or rows and 61 **variables** or columns. The raw data is already living in R. That is how rows and columns are called in data science jargon: observations and variables. Remember that because you will be seeing it a lot.

Now, if you double-click on the myXL object R automatically will open a data viewer for you.

<img src="https://media.licdn.com/mpr/mpr/AAEAAQAAAAAAAAuBAAAAJGRjZWM4OWNiLWY1NDMtNDZhMS04OWE3LWY1ZjZiYWM3ZjI3MA.jpg" width="600px" />

You can get the raw data file `oilfield_100w_raw_data.xlsx` via [GitHub](https://github.com/f0nzie/rNodal.oilwells/blob/master/inst/extdata/oilfield_100w_raw_data.xlsx). Download the file and start practicing opening the file and loading it in R.

The notebook is your friend
---------------------------

Another thing that you will notice in this lecture is that we can combine text, math, equations and results in the same document. As a matter of fact, I am writing all of this in a R Markdown document or notebook. You can see it as the README of the package in GitHub here. It is the file README.md in green highlight.

<img src="https://media.licdn.com/mpr/mpr/AAEAAQAAAAAAAAvDAAAAJGMwYzIyODg4LTRkOTMtNDgyOS1hYjk1LTUwMjczNjc1OGI0OA.jpg" width="600px" />

Writing project or analysis documentation this way is not only useful but a time saver. You don't need to type your text in Word, for instance, and copy-paste the calculations or plots in the document afterwards. And most important of all, you reduce the chance of errors. You will see for yourself later when we mix calculations inside and together with the text.

Some well data anatomy
----------------------

Some data introspection
-----------------------

``` r
print(myXl)
#>          Wellname       Company  Analyst Field Location Platform Fluid
#> 1    PSCO-M005-TS Oil Gains Co.     Aida PISCO  M005-TS        M     0
#> 2   PSCO-M0007-TS Oil Gains Co.     Aida PISCO  M007-TS        M     0
#> 3    PSCO-M004-LS Oil Gains Co.     Aida PISCO  M004-LS        M     0
#> 4    PSCO-M008-TS Oil Gains Co.     Aida PISCO  M008-TS        M     0
#> 5    PSCO-M010-SS Oil Gains Co.     Aida PISCO  M010-SS        M     0
#> 6    PSCO-M006-TS Oil Gains Co.     Aida PISCO  M006-TS        M     0
#> 7    PSCO-m016-LS Oil Gains Co. Ibironke  <NA>  M016-LS        M     0
#> 8    PSCO-M018-LS Oil Gains Co. Ibironke PISCO  M018-LS        M     0
#> 9    PSCO-M021-LS Oil Gains Co.  Ibironk PISCO  M021-LS        M     0
#> 10   PSCO-M017-LS Oil Gains Co. Ibironke PISCO  M017-LS        M     0
#> 11   PSCO-M030-SS Oil Gains Co. Ibironke PISCO  M030-SS        M     0
#> 12   PSCO-M027-SS Oil Gains Co. Ibironke pisco  M027-SS        M     0
#> 13   PSCO-M016-SS Oil Gains Co. Ibironke PISCO  M016-SS        M     0
#> 14   PSCO-M020-LS Oil Gains Co. Ibironke PISCO  M020-LS        M     0
#> 15   PSCO-M028-TS Oil Gains Co. Ibironke PISCO  M028-TS        M     0
#> 16   PSCO-M015-LS Oil Gains Co.    Vivek PISCO  M015-LS        M     0
#> 17   PSCO-M018-SS Oil Gains Co.    Vivek PISCO  M018-SS        M     0
#> 18   PSCO-M015-SS Oil Gains Co.    Vivek PISCO  M015-SS        M     0
#> 19   PSCO-M002-LS Oil Gains Co.    Vivek PISCO     <NA>        M     0
#> 20   PSCO-M012-TS Oil Gains Co.    Vivek PISCO  M012-TS        M     0
#> 21   PSCO-Q007-LS Oil Gains Co.  Americo PISCO  Q007-LS        Q     0
#> 22    PSCO-Q001-S Oil Gains Co.  Americo PISCO  Q001-SS        Q     0
#> 23   PSCO-Q005-SS Oil Gains Co.  Americo PISCO  Q005-SS        Q     0
#> 24   PSCO-Q011-SS Oil Gains Co.  Americo PISCO  Q011-SS        Q     0
#> 25   PSCO-Q002-SS Oil Gains Co.  Americo PISCO  Q002-SS        Q     0
#> 26   PSCO-Q002-LS Oil Gains Co.  Americo PISCO  Q002-LS        Q     0
#> 27   PSCO-Q003-LS Oil Gains Co. Ibironke pisco  Q003-LS        Q     0
#> 28   PSCO-Q004-SS Oil Gains Co. Ibironke PISCO  Q004-SS        Q     0
#> 29   PSCO-Q009-SS Oil Gains Co.    Vivek PISCO  Q009-SS        Q     0
#> 30    PSCO-Q019-L Oil Gains Co.   Norman PISCO  Q019-LS        Q     0
#> 31   PSCO-Q032-SS Oil Gains Co.      Rod PISCO  Q032-SS        Q     0
#> 32   PSCO-Q028-LS Oil Gains Co.      Rod PISCO  Q028-LS        Q     0
#> 33   PSCO-Q028-SS Oil Gains Co.      Rod PISCO  Q028-SS        Q     0
#> 34   PSCO-Q029-LS Oil Gains Co.  Rodrigo PISCO  Q029-LS        Q     0
#> 35   PSCO-Q032-LS Oil Gains Co.  Rodrigo PISCO  Q032-LS        Q     0
#> 36   PSCO-Q024-TS Oil Gains Co.      Sam PISCO  Q024-TS        Q     0
#> 37   PSCO-Q018-LS Oil Gains Co.   Thomas PISCO  Q018-LS        Q     0
#> 38   PSCO-Q017-LS Oil Gains Co.      Tom PISCO  Q017-LS        Q     0
#> 39   PSCO-Q013-SS Oil Gains Co.      Tom PISCO  Q013-SS        Q     0
#> 40   PSCO-Q014-LS Oil Gains Co.      Tom PISCO  Q014-LS        Q     0
#> 41   PSCO-Q017-SS Oil Gains Co.      Tom PISCO  Q017-SS        Q     0
#> 42   PSCO-Q014-SS Oil Gains Co.      Tom PISCO  Q014-SS        Q     0
#> 43   PSCO-Q018-SS Oil Gains Co.      Tom PISCO  Q018-SS        Q     0
#> 44   PSCO-Q012-TS Oil Gains Co.      Tom PISCO  Q012-TS        Q     0
#> 45  PiSCO-R009-SS Oil Gains Co.     Aida PISCO  R009-SS        R     0
#> 46   PSCO-r015-LS Oil Gains Co.    Vivek PISCO  R015-LS        R     0
#> 47   PSCO-R019-SS Oil Gains Co.    Vivek PISCO  R019-SS        R     0
#> 48   PSCO-R019-LS Oil Gains Co.    Vivek PISCO  R019-LS        R     0
#> 49   PSCO-R020-SS Oil Gains Co.    Vivek PISCO  R020-SS        R     0
#> 50   PSCO-R013-TS Oil Gains Co.    Vivek PISCO  R013-TS        R     0
#> 51   PSCO-R012-LS Oil Gains Co.    Vivek PISCO  R012-LS        R     0
#> 52   PSCO-R012-SS Oil Gains Co.    Vivek PISCO  R012-SS        R     0
#> 53   PSCO-R018-SS Oil Gains Co.    Vivek PISCO  R018-SS        R     0
#> 54   PSCO-R018-LS Oil Gains Co.    Vivek PISCO  R018-LS        R     0
#> 55   PSCO-R015-SS Oil Gains Co.    Vivek PISCO  R015-SS        R     0
#> 56   PSCO-R020-SS Oil Gains Co.    Vivek PISCO  R020-SS        R     0
#> 57   PSCO-R004-LS Oil Gains Co.      Kai PISCO  R004-LS        R     0
#> 58   PSCO-R001-SS Oil Gains Co.      Kai PISCO  R001-SS        R     0
#> 59   PSCO-R003-TS Oil Gains Co.      Kai PISCO  R003-TS        R     0
#> 60   PSCO-R006-SS Oil Gains Co.      Kai PISCO  R006-SS        R     0
#> 61   PSCO-R007-LS Oil Gains Co.      Kai PISCO  R007-LS        R     0
#> 62   PSCO-R001-LS Oil Gains Co.      Kai PISCO  R001-LS        R     0
#> 63   PSCO-R007-SS Oil Gains Co.      Kai PISCO  R007-SS        R     0
#> 64   PSCO-R002-SS Oil Gains Co.      Kai PISCO  R002-SS        R     0
#> 65   PSCO-R029-TS Oil Gains Co.   Norman PISCO  R029-TS        R     0
#> 66  PISCO-R027-LS Oil Gains Co.   Norman PISCO  R027-LS        R     0
#> 67   PSCO-R025-SS Oil Gains Co.   Norman PISCO  R025-SS        R     0
#> 68   PSCO-R023-SS Oil Gains Co.   Norman PISCO  R023-SS        R     0
#> 69    PSCO-R022-T Oil Gains Co.   Norman PISCO  R022-TS        R     0
#> 70   PSCO-R021-SS Oil Gains Co.   Norman PISCO  R021-SS        R     0
#> 71   PSCO-R023-LS Oil Gains Co.   Norman PISCO  R023-LS        R     0
#> 72   PSCO-R027-SS Oil Gains Co.   Norman PISCO  R027-SS        R     0
#> 73   PSCO-S008-LS Oil Gains Co.   Andrew PISCO  S008-LS        S     0
#> 74   PSCO-S004-LS Oil Gains Co.   Andrew PISCO  S004-LS        S     0
#> 75    PSCO-027-TS Oil Gains Co.   Andrew PISCO  S027-TS        S     0
#> 76   PSCO-S019-SS Oil Gains Co.   Andrew PISCO  S019-SS        S     0
#> 77   PSCO-S007-LS Oil Gains Co.   Andrew PISCO  S007-LS        S     0
#> 78   PSCO-S011-SS Oil Gains Co.     Andy PISCO  S011-SS        S     0
#> 79   PSCO-S016-LS Oil Gains Co.   Andrew PISCO  S016-LS        S     0
#> 80   PSCO-S002-TS Oil Gains Co.   Andrew PISCO  S002-TS        S     0
#> 81   PSCO-S002-TS Oil Gains Co.   Andrew PISCO  S002-TS        S     0
#> 82  PSCO-S019 -LS Oil Gains Co.   Andrew PISCO  S019-LS        S     0
#> 83   PSCO-S030-SS Oil Gains Co.     Andy PISCO  S030-SS        S     0
#> 84   PSCO-S018-LS Oil Gains Co.   Camden PISCO  S018-LS        S     0
#> 85   PSCO-S026-SS Oil Gains Co.   Camden PISCO  S026-SS        S     0
#> 86   PSCO-S029-TS Oil Gains Co.   Camden PISCO  S029-TS        S     0
#> 87   PSCO-S018-SS Oil Gains Co.   Camden PISCO  S018-SS        S     0
#> 88   PSCO-S013-SS Oil Gains Co.   Camden PISCO  S013-SS        S     0
#> 89   PSCO-S015-LS Oil Gains Co.   Camden PISCO  S015-LS        S     0
#> 90   PSCO-S031-TS Oil Gains Co.   Camden PISCO  S031-TS        S     0
#> 91   PSCO-S032-SS Oil Gains Co.   Camden PISCO  S032-SS        S     0
#> 92   PSCO-S030-LS Oil Gains Co.   Camden PISCO  S030-LS        S     0
#> 93   PSCO-S032-LS Oil Gains Co.   Camden PISCO  S032-LS        S     0
#> 94   PSCO-S006-SS Oil Gains Co.   Camden PISCO  S006-SS        S     0
#> 95   PSCO-S021-TS Oil Gains Co.   Camden PISCO  S021-TS        S     0
#> 96   PSCO-S016-SS Oil Gains Co.   Camden PISCO  S016-SS        S     0
#> 97   PSCO-S015-SS Oil Gains Co.   Camden PISCO  S015-SS        S     0
#> 98   PSCO-S012-LS Oil Gains Co.     <NA> PISCO  S012-LS        S     0
#> 99   PSCO-M001-TS Oil Gains Co.     Aida PISCO  M001-TS     <NA>     0
#> 100 PSCO-M0026-TS Oil Gains Co. Ibironke PISCO  M026-TS     <NA>     0
#>     WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 1          0         1          0           0       27 445.700 36.0000
#> 2          0         1          0           0       22 473.000 36.0000
#> 3          0         1          0           0       11 280.000 36.0000
#> 4          0         1          0           0       14 414.000 36.0000
#> 5          0         1          0           0       13 420.000 35.2000
#> 6          0         0          0           0       20 416.000 36.0000
#> 7          0         1          0           0        3 419.775 35.0000
#> 8          0         1          0           0        2 415.875 36.0000
#> 9          0         1          0           0        2 415.875 36.0000
#> 10         0         1          0           0        2 415.875 36.0000
#> 11         0         1          0           0        2 413.554 36.0000
#> 12         0         1          0           0        3 413.554 36.0000
#> 13         0         1          0           0        3 413.554 36.0000
#> 14         0         1          0           0        3 472.896 36.0000
#> 15         0         1          0           0        1 415.875 36.0000
#> 16         0         1          0           0        1 419.775 36.0000
#> 17         0         1          0           0        1 415.875 36.0000
#> 18         0         1          0           0        1 413.554 36.0000
#> 19         0         1          0           0        1 415.875 36.0000
#> 20         0         1          0           0        1 445.700 36.6000
#> 21         0         1          0           0       12 416.000 36.0000
#> 22         0         1          0           0       11 420.000 36.0000
#> 23         0         1          0           0        8 420.000 36.0000
#> 24         0         1          0           0        8 445.700 36.0000
#> 25         0         1          0           0        2 426.000 36.0000
#> 26         0         1          0           0        1 416.000 36.0000
#> 27         0         1          0           0        3 472.896 36.0000
#> 28         0         1          0           0        1 415.875 36.0000
#> 29         0         1          0           0        1 415.875 36.0000
#> 30         0         1          0           0        2 415.875 36.0000
#> 31         0         1          0           0        4 416.000 36.0000
#> 32         0         1          0           0        1 472.000 36.0000
#> 33         0         1          0           0        1 472.000 36.0000
#> 34         0         1          0           0        2 416.000 36.0000
#> 35         0         1          0           0        1 473.000 36.0000
#> 36         0         1          0           0        9 472.896 36.0000
#> 37         0         1          0           0        1 416.000 36.0000
#> 38         0         1          0           0        3 416.000 36.0000
#> 39         0         0          0           0        1 413.554 46.1535
#> 40         0         1          0           0        1 416.000 36.0000
#> 41         0         1          0           0        1 416.000 36.0000
#> 42         0         1          0           0        1 426.000 36.0000
#> 43         0         1          0           0        1 416.000 36.0000
#> 44         0         1          0           0        1 426.000 36.0000
#> 45         0         1          0           0       15 420.000 36.0000
#> 46         0         1          0           0        2 416.000 36.0000
#> 47         0         1          0           0        2 426.000 36.0000
#> 48         0         1          0           0        4 420.000 36.0000
#> 49         0         1          0           0       12 414.000 36.0000
#> 50         0         1          0           0       12 413.554 36.0000
#> 51         0         1          0           0       11 416.000 36.0000
#> 52         0         1          0           0        6 413.000 36.0000
#> 53         0         1          0           0        3 426.000 36.0000
#> 54         0         1          0           0        3 426.000 36.0000
#> 55         0         1          0           0        1 420.000 36.0000
#> 56         0         1          0           0        1 413.554 36.0000
#> 57         0         1          0           0        5 419.000 36.0000
#> 58         0         1          0           0        2 419.000 36.0000
#> 59         0         1          1           3        2 426.000 39.0000
#> 60         0         1          0           0        2 426.000 36.0000
#> 61         0         1          0           0       10 426.000 36.0000
#> 62         0         1          0           0        5 415.000 37.0000
#> 63         0         1          0           0        3 419.000 36.0000
#> 64         0         1          0           0        1 426.000 36.0000
#> 65         0         1          0           0        4 415.875 36.0000
#> 66         0         1          0           0        2 472.896 36.0000
#> 67         0         1          0           0        4 426.008 36.0000
#> 68         0         1          0           0        3 426.008 36.0000
#> 69         0         1          1           3        3 419.775 36.0000
#> 70         0         1          0           0        1 413.554 36.0000
#> 71         0         1          0           0        1 419.775 36.0000
#> 72         0         1          0           0        1 419.775 36.0000
#> 73         0         1          0           0        3 455.183 36.1000
#> 74         0         1          0           0        2 455.183 36.0000
#> 75         0         1          1           3        7 455.183 36.1000
#> 76         0         1          0           0        3 446.000 36.1000
#> 77         0         1          0           0       10 455.183 36.1000
#> 78         0         1          0           0        9 455.183 36.0000
#> 79         0         1          0           0        3 455.183 36.1000
#> 80         0         1          0           0        1 455.183 36.0000
#> 81         0         1          0           0        1 455.183 36.0000
#> 82         0         1          0           0        1 455.183 36.1000
#> 83         0         1          1           3        8 439.000 36.0000
#> 84         0         1          0           0        3 455.183 36.1000
#> 85         0         1          0           0       10 455.183 36.1000
#> 86         0         1          1           3        8 455.183 36.1000
#> 87         0         1          0           0        6 450.747 36.0000
#> 88         0         1          0           0        4 450.747 36.0000
#> 89         0         1          0           0        3 455.183 36.8000
#> 90         0         1          1           0        4 455.183 36.0000
#> 91         0         1          0           3        6 450.747 36.0000
#> 92         0         1          1           3        9 455.183 36.1000
#> 93         0         1          0           3        4 455.183 36.1000
#> 94         0         1          0           0        7 446.000 36.1000
#> 95         0         1          0           0        9 455.183 36.1000
#> 96         0         1          0           0        4 450.747 36.0000
#> 97         0         1          0           0        3 450.747 36.1000
#> 98         0         1          0           0        2 350.000 36.0000
#> 99         0         1          0           0       19 473.000 36.0000
#> 100        0         1          0           0        2 472.896 36.0000
#>     PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 1      1.20000             25000       0   65.50           3             2
#> 2      1.20000             25000       0   65.00           3             2
#> 3      1.20000             25000       0   65.00           3             2
#> 4      1.20000             25000       0   65.00           3             2
#> 5      1.20000             25000       0   65.00           3             2
#> 6      1.20000             25000       0   65.00           3             2
#> 7      1.20000             15000       0   65.00           3             4
#> 8      1.20000             15000       0   65.00           3             2
#> 9      1.20000             15000       0   65.00           3             0
#> 10     1.20000             15000       0   65.00           3             2
#> 11     1.20000             15000       0   65.00           3             2
#> 12     1.20000             15000       0   65.00           3             2
#> 13     1.20000             15000       0   65.00           3             2
#> 14     1.20000             15000       0   65.00           3             2
#> 15     1.20000             15000       0   65.00           3             2
#> 16     1.20000             15000       0   65.00           3             2
#> 17     1.20000             15500       0   65.00           3             2
#> 18     1.20000             15500       0   65.00           3             2
#> 19     1.20000             15500       0   65.00           3             2
#> 20     1.20000             25000       0   65.00           3             2
#> 21     1.20000             15500       0   65.00           3             2
#> 22     1.20000             15000       0   65.00           3             2
#> 23     1.20000             15500       0   65.00           3             2
#> 24     1.20000             15500       0   65.00           3             2
#> 25     1.20000             15500       0   65.00           0             1
#> 26     1.20000             15500       0   65.00           3             2
#> 27     1.20000             15000       0   65.00           3             2
#> 28     1.20000             15000       0   65.00           3             2
#> 29     1.20000             15500       0   65.00           3             2
#> 30     1.20000             15000       0   65.00           3             2
#> 31     1.21562             15500       0   65.00           3             2
#> 32     1.20000             15000       0   69.00           3             2
#> 33     1.20000             15000       0   69.00           3             2
#> 34     1.20000             15000       0   69.00           3             2
#> 35     1.20000             15000       0   65.00           3             2
#> 36     1.20000             15000       0   69.00           3             2
#> 37     1.20000             15500       0   65.00           3             1
#> 38     1.20000             15000       0   65.00           3             4
#> 39     0.80000             15000       0   29.00           0             1
#> 40     1.20000             15000       0   65.00           3             4
#> 41     1.20000             15000       0   65.00           3             4
#> 42     1.20000             16700       0   65.00           3             3
#> 43     1.20000             15500       0   65.00           3             1
#> 44     1.20000             15000       0   65.00           3             4
#> 45     1.20000             25000       0   65.00           3             2
#> 46     1.20000             12000       0   65.00           2             2
#> 47     1.20000             15000       0   65.00           2             2
#> 48     1.20000             15000       0   65.00           2             2
#> 49     1.20000             15000       0   65.00           0             2
#> 50     1.20000             15000       0   65.00           2             2
#> 51     1.20000              1000       0   65.00           0             2
#> 52     1.20000             10000       0   65.00           2             2
#> 53     1.20000             15000       0   65.00           2             2
#> 54     1.20000             15000       0   65.00           2             2
#> 55     1.20000             12000       0   65.00           3             2
#> 56     1.20000             15000       0   65.00           3             2
#> 57     1.20000             15000       0   65.00           3             2
#> 58     1.20000             10000       0   65.00           3             2
#> 59     1.20000             15000       0   65.00           3             2
#> 60     1.20000             12000       0   65.00           3             2
#> 61     1.20000             15000       0   65.00           3             4
#> 62     1.20000             10000       0   65.00           3             2
#> 63     1.20000             15000       0   65.00           3             2
#> 64     1.20000             15000       0   65.00           3             4
#> 65     1.20000             15000       0   65.00           3             2
#> 66     1.20000             15000       0   65.00           3             2
#> 67     1.20000             15000       0   65.00           3             2
#> 68     1.20000             15000       0   65.00           3             2
#> 69     1.20000             15000       0   65.00           3             1
#> 70     1.20000             15000       0   65.00           3             2
#> 71     1.20000             15000       0   65.00           3             2
#> 72     1.20000             15000       0   65.00           3             2
#> 73     1.30000             10000       0   74.00           3             1
#> 74     1.30000             15000       0   73.00           3             1
#> 75     1.30000             10000       0   74.00           3             1
#> 76     1.20000             10000       0   65.00           3             1
#> 77     1.30000             10000       0   70.00           3             1
#> 78     1.30000             15000       0   70.00           3             1
#> 79     1.30000             15000       0   70.00           3             0
#> 80     1.30000             15000       0   73.00           3             1
#> 81     1.30000             15000       0   73.00           3             1
#> 82     1.30000             10000       0   74.00           3             1
#> 83     1.30000             15000       0   74.00           3             2
#> 84     1.30000             15000       0   70.00           3             0
#> 85     1.30000             10000       0   74.00           3             0
#> 86     1.30000             10000       0   74.00           3             1
#> 87     1.30000             10000       0   70.00           3             1
#> 88     1.30000             10000       0   70.00           3             1
#> 89     1.30000             30000       0   70.00           3             0
#> 90     1.30000             15000       0   73.00           3             1
#> 91     1.30000             10000       0   70.00           3             1
#> 92     1.30000             15000       0   70.00           3             0
#> 93     1.30000             10000       0   74.00           3             1
#> 94     1.30000             10000       0   74.28           3             1
#> 95     1.30000             10000       0   74.00           3             1
#> 96     1.30000             10000       0   70.00           3             1
#> 97     1.30000             30000       0   74.00           3             1
#> 98     1.30000             20000       0   70.00           0             0
#> 99     1.20000             25000       0   65.00           3             2
#> 100    1.20000             15000       0   65.00           3             2
#>     PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 1    209.00000   1821.000       10        0     930.000    209.0000
#> 2    209.00000   1921.000       10        0    1300.000    209.0000
#> 3    209.00000   1753.000        1        1    1573.000    209.0000
#> 4    209.00000   1698.000       10        1    1286.000    200.0000
#> 5    209.00000   1722.000       10        0    1468.000    209.0000
#> 6    209.00000   1753.000       10        0    1286.000    209.0000
#> 7    209.00000   1722.000       10        0    1459.500    214.0000
#> 8    209.00000   1753.000       10        1    1107.000    211.0000
#> 9    209.00000   1753.000       10        1    1526.000    202.0000
#> 10   209.00000   1753.000       10        0    1311.700    216.0000
#> 11   209.00000   1698.000       10        0    1236.000    159.0000
#> 12   209.00000   1698.000       10        0    1034.000    203.0000
#> 13   209.00000   1698.000       10        0    1407.000    209.0000
#> 14   209.00000   1921.000       10        1    1600.000    220.0000
#> 15   209.00000   1753.000       10        0    1206.000    208.0000
#> 16   209.00000   1722.000       10        0    1028.790    209.0000
#> 17   209.00000   1753.000       10        0    1526.000    209.0000
#> 18   209.00000   1698.000       10        0    1407.000    209.0000
#> 19   209.00000   1753.000       10        0    1312.000    209.0000
#> 20   209.00000   1821.000       10        0    1126.000    209.0000
#> 21   209.00000   1753.000        0        0     850.000    208.2000
#> 22   209.00000   1736.696       12        0     800.000    209.0000
#> 23   209.00000   1722.000        0        0    1300.000    209.0000
#> 24   209.00000   1722.000       12        0    1285.300    209.0000
#> 25   408.20004   1731.304       10        0    1085.304    209.0000
#> 26   209.00000   1753.000       10        0    1600.000    209.0000
#> 27   209.00000   1921.000       10        0    1300.000    224.0000
#> 28   209.00000   1753.000       10        0    1313.000    210.0000
#> 29   209.00000   1753.000       10        0     850.000    209.0000
#> 30   209.00000   1753.000       10        1     658.000    205.0000
#> 31   209.00000   1767.696       10        0    1300.000    209.0000
#> 32   209.00000   1921.000       10        1    1560.710    210.0000
#> 33   209.00000   1921.000       10        1    1560.710    210.0000
#> 34   209.00000   1753.000       10        1    1088.030    212.0000
#> 35   209.00000   1921.000       10        0    1400.000    211.0000
#> 36   209.00000   1921.000       10        0    1500.000    210.0000
#> 37   408.20001   1738.300       10        0    1080.000    212.0000
#> 38   209.00000   1738.304       10        0    1441.000    206.0000
#> 39   209.00000   1683.304       10        0    2727.000    209.0000
#> 40   209.00000   1738.304       10        0    1225.000    212.0000
#> 41   209.00000   1738.304       10        0    1250.000    205.0000
#> 42   209.00000   1731.300       10        0    1161.000    200.0000
#> 43   408.20004   1738.304       10        0    1036.000    205.0000
#> 44   209.00000   1731.300       10        0    1611.000    200.0000
#> 45   209.00000   1722.000       10        0    1546.000    209.0000
#> 46   209.00000   1753.000       10        1     951.000    209.0000
#> 47   209.00000   1746.000       10        1    1374.000    209.0000
#> 48   209.00000   1722.000       10        1    1272.000    209.0000
#> 49   408.20004   1698.000       10        1    1539.000    209.0000
#> 50   209.00000   1698.000       10        1    1236.000    209.0000
#> 51   209.00000   1753.000       10        1    1663.000    209.0000
#> 52   209.00000   1698.000       10        1    1243.000    209.0000
#> 53   209.00000   1746.000       10        1    1750.000    209.0000
#> 54   209.00000   1722.000       10        1    1367.000    209.0000
#> 55   209.00000   1722.000       10        1    1247.000    209.0000
#> 56   209.00000   1698.000       10        1    1058.260    206.0160
#> 57   209.00000   1722.000       10        0    1224.000    206.0000
#> 58   203.00000   1722.000       10        1     810.000    201.0000
#> 59   209.00000   1746.000       10        0    1380.000    214.0000
#> 60   209.00000   1746.000       10        1    1550.000    215.0000
#> 61   208.99995   1746.000       10        0    1663.000    211.0000
#> 62   209.00000   1753.000       10        0    1615.000    206.0000
#> 63   209.00000   1722.000       10        1    1550.000    206.0000
#> 64   209.00000   1746.000       18        0     930.314    211.0000
#> 65   209.00000   1753.000       10        1    1400.000    210.0000
#> 66   209.00000   1935.700       10        1    1373.090    215.7700
#> 67   209.00000   1746.000       10        1    1407.000    218.4000
#> 68   209.00000   1746.000       10        0    1566.000    213.3200
#> 69   209.00000   1722.000       10        1    1400.000    203.0000
#> 70   209.00000   1698.000       10        0    1339.000    121.7560
#> 71   209.00000   1722.000       10        1    1536.000    210.4600
#> 72   209.00000   1722.000       10        0    1367.000    207.2000
#> 73   208.00006   1850.696       10        1    1574.696    208.0001
#> 74   208.00000   1836.000       10        1    1599.996    215.0006
#> 75   208.00000   1850.696       10        1    1695.700    217.9990
#> 76   206.00000   1808.696       10        1    1114.700    205.0000
#> 77   208.00000   1836.000       10        1    1560.000    226.0000
#> 78    97.77777   1836.000       10        1    1485.000    107.5780
#> 79   208.00000   1835.996       10        1    1513.700    223.0000
#> 80   208.00000   1836.000       10        0    1400.000    215.0010
#> 81   208.00000   1836.000       10        0    1400.000    215.0010
#> 82   208.00000   1850.696       10        1    1695.696    217.9994
#> 83   208.00000   1835.696       10        1    1480.750    206.0000
#> 84   208.00000   1821.304       10        1    1425.300    223.0000
#> 85   208.00006   1850.696       10        1    1591.696    208.0001
#> 86   208.00006   1850.696       10        1    1574.700    212.0000
#> 87   208.00000   1821.000       10        1    1479.996    206.0001
#> 88   208.00000   1821.000       10        0    1664.700    206.0000
#> 89   208.00000   1850.696       18        1    1564.700    208.0000
#> 90   208.00000   1836.000       10        1    1685.996    212.0000
#> 91   208.00000   1821.000       10        1    1591.696    206.0001
#> 92   208.00006   1835.996       10        1    1664.700    214.0000
#> 93   208.00006   1850.696       10        1    1622.700    208.0000
#> 94   206.00000   1808.696       18        1    1414.696    205.0000
#> 95   208.00000   1850.700       10        1    1664.696    208.0001
#> 96   208.00000   1821.000       10        1    1580.000    206.0000
#> 97   208.00006   1835.696       18        1    1494.700    208.0000
#> 98          NA         NA       10        3    1620.696    206.0000
#> 99   209.00000   1921.000       10        0    1388.000    209.0000
#> 100  209.00000   1921.000       10        0    1600.000    210.0000
#>     IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES    IPR_PI         GEO_THMD
#> 1     1449.000  66.00      384.00       331.000  4.560000        0|2289.5|
#> 2     1581.500  70.00      973.70       956.000  1.150000          0|1744|
#> 3     1235.000   0.00     1327.00       941.436  0.710000       0|1954.09|
#> 4     4867.000   5.00      150.80       418.464  0.250000          0|1720|
#> 5      420.000  90.00     1290.30       430.877  1.350000          0|2308|
#> 6     6000.000  80.00      559.00       902.000  7.800000       0|1496.87|
#> 7     3676.000  90.00      560.00       981.644  1.018000      14.52|1954|
#> 8      544.000  95.00      560.40      1038.140  3.135000    14.52|1684.5|
#> 9     4735.000  90.00      440.80       873.840  0.688000   14.52|1543.02|
#> 10    3804.000  90.00      718.10      1142.160  2.760000          0|1890|
#> 11    1127.000  90.00      345.90       793.279  0.800000   14.52|1781.52|
#> 12    1072.000  56.00      257.60       688.724  0.810000     14.6|2423.5|
#> 13    1354.000  95.00      559.70       829.834  0.985000   14.52|1914.32|
#> 14    1923.000  87.37     2131.50      1328.500  2.000000   14.52|1442.42|
#> 15    2615.700  60.00      558.90       802.695  1.500000        0|2169.8|
#> 16    4140.000  76.00        0.00         0.000  7.300000        0|1962.5|
#> 17    7727.000  90.03        0.00         0.000  0.830000        0|1700.5|
#> 18     413.554   0.00        0.00         0.000  0.830000          0|1874|
#> 19    2103.600  89.90        0.00         0.000  1.925000          0|2015|
#> 20    4000.000  80.00        0.00         0.000  1.580000          0|2660|
#> 21    2000.000  55.00        0.00         0.000  7.435303       0|1569.62|
#> 22     557.000   8.00      568.00       364.696  2.300000        0|1254.8|
#> 23    1500.000  60.00        0.00         0.000  6.200000          0|2055|
#> 24    2500.000  73.84        0.00         0.000  5.520013          0|1720|
#> 25    2308.000  95.00     1039.00       943.500  2.690000          0|1474|
#> 26     845.000  89.50        0.00         0.000  2.243000          0|1590|
#> 27    4824.000  95.00      895.80      1068.970  3.900000   13.83|2218.53|
#> 28    1579.000  90.00     1477.10       916.945  3.800000       0|1362.74|
#> 29     415.875   2.78        0.00         0.000  5.660000       0|1630.75|
#> 30    1500.000  53.82      210.40       440.962  0.800000   0|1000|1541.4|
#> 31    6000.000  95.00        0.00         0.000  2.000000          0|2538|
#> 32    1597.000  79.00     1730.00       951.197  0.000000          0|1458|
#> 33    1839.000  79.00     1730.00       860.542  0.000000          0|1458|
#> 34    7500.000  81.00      397.00       497.414  0.000000          0|1730|
#> 35     952.000  71.00        0.00         0.000  5.861280        0|2682.4|
#> 36    1464.000  70.00     2420.77       983.025  5.121770          0|1470|
#> 37    2467.000  82.00        0.00         0.000  2.160971          0|1761|
#> 38     733.000  44.80      605.12       795.304  6.300000        0|1832.7|
#> 39   11229.000   0.00        0.00         0.000  6.919375          0|2222|
#> 40    1582.000  88.00        0.00         0.000  5.500000       0|1862.12|
#> 41     516.000  63.00     1189.00       871.000  5.020470        0|1763.7|
#> 42     426.000   0.00        0.00         0.000  3.350000        0|1783.6|
#> 43     995.000  54.00        0.00         0.000  1.450000       0|1735.24|
#> 44    6638.000  90.40        0.00         0.000  0.370000          0|2043|
#> 45    1435.000  80.00        0.00         0.000  3.000000       0|1667.08|
#> 46    3108.000  80.00      580.00       718.604  1.270000        0|2263.7|
#> 47    1772.000  85.00      714.76       771.077  1.250000        0|1910.1|
#> 48    7443.000  90.00     1155.40       906.265  1.500000 0|1929.4|1949.7|
#> 49    1654.000  85.00     1347.00      1190.210  8.900000        0|2442.3|
#> 50     596.000  40.00      596.00       691.101  8.000000          0|1648|
#> 51    1714.000  85.00     1207.00       975.827  1.830000        0|1519.5|
#> 52     807.000  80.00     1364.00       991.177 10.000000          0|1520|
#> 53    3804.000  95.00     1932.00      1328.700  2.464140        0|1921.5|
#> 54   10424.000  95.00     1065.00       902.479  2.464140        0|1994.7|
#> 55    1719.000  51.00     1353.00       980.503  1.270000        0|2263.7|
#> 56    1114.900  60.00     1192.20       936.090  0.000000     0|2430|2703|
#> 57    1716.000  80.00      814.00      1156.000  1.410000        0|2312.5|
#> 58     675.000  35.00      898.00       717.410  5.000000        0|1409.3|
#> 59     426.000  50.00        0.00         0.000  7.400000      0|100|1891|
#> 60     500.000  60.00      331.00      1140.000  0.814380          0|1371|
#> 61     426.000  90.00        0.00         0.000  1.580000        0|1260.4|
#> 62     415.000  50.00     1200.00       992.000  4.786520        0|1477.6|
#> 63     600.000  70.00     1250.00      1261.650  1.833730        0|1278.8|
#> 64     426.000  60.00        0.00         0.000  1.480000        0|1525.8|
#> 65     404.000  30.00     1891.10      1082.400 12.000000     0|2426|2620|
#> 66     762.000  60.00     1179.30      1031.980  4.400000     0|2252|2580|
#> 67    1014.000  20.00      370.00       675.989  0.000000   0|1200|1299.7|
#> 68    2098.800  90.47     1421.10       979.644  1.308000     0|1584|1810|
#> 69    1625.900  80.00     1141.60       758.608  2.590000          0|1663|
#> 70    2958.000  85.62     1799.20      1310.000  2.240000     0|1830|2135|
#> 71     674.540  90.45     1166.80      1188.620  7.000000     0|1638|1810|
#> 72    1779.200  35.03      416.10      1089.690  0.677000     0|2300|2617|
#> 73     500.000  85.00      330.00       743.749  0.800000       0|7273.62|
#> 74     720.000  19.00      763.60       656.284  0.580000        0|5856.3|
#> 75     700.000   2.00     1075.00       736.188  1.550000       0|5141.08|
#> 76    2674.000  60.00     1004.00       975.861  0.755000       0|6542.98|
#> 77     507.000  50.76      507.10       912.957  2.200000       0|5583.99|
#> 78     940.000  44.00      362.00       668.011  0.628750       0|9186.35|
#> 79     530.000  51.00      286.00       860.421  0.500000       0|4734.58|
#> 80     632.000  70.00        0.00         0.000  1.860078       0|5347.77|
#> 81     632.000  70.00        0.00         0.000  1.860078       0|5347.77|
#> 82     850.000  50.69     1082.20       589.100  1.400000       0|7372.05|
#> 83     500.000  17.00      396.00       715.239  0.700000       0|4757.22|
#> 84     530.000  62.00      317.80       658.660  0.400000       0|4558.07|
#> 85     658.000  62.00      200.00      1068.786  1.200000       0|9500.98|
#> 86     500.000  52.00      658.00       851.995  0.800000       0|8874.67|
#> 87     569.000  69.00      864.00      1021.896  2.000000       0|4503.94|
#> 88    1259.000  96.00        0.00         0.000  1.782440       0|4289.04|
#> 89     592.000  47.00      492.00       673.926  0.680000       0|6289.37|
#> 90     513.000  18.00      396.00       713.689  0.500000       0|6056.43|
#> 91    1000.000  69.00      250.00       692.188  0.800000       0|5521.65|
#> 92     500.000  71.00     2398.00      1381.096  9.000000       0|4652.23|
#> 93     500.000  71.00     1634.00      1053.136  3.050000       0|6089.24|
#> 94    1000.000  52.00      359.00       555.593  1.690000        0|6952.1|
#> 95    1500.000  75.00      100.00      1202.016  2.300000       0|13556.4|
#> 96     558.700  64.89     1664.00      1214.996  1.650000       0|4921.26|
#> 97    7737.000  52.00     1087.00       949.975  2.600000       0|6008.86|
#> 98    2821.670  90.00        0.00         0.000  1.000000       0|4507.87|
#> 99    3572.000  89.60      560.00      1029.900  1.480000          0|1568|
#> 100   1009.000  80.00      784.60      1043.270  1.471000          0|1593|
#>                  GEO_THTEMP GL_method
#> 1                   90|209|         0
#> 2                   90|200|         0
#> 3                   80|200|         2
#> 4                   90|200|         2
#> 5                   90|200|         0
#> 6                   90|200|         2
#> 7                   92|214|         0
#> 8                   86|211|         0
#> 9                   80|202|         0
#> 10                 104|216|         0
#> 11                  92|159|         0
#> 12                  95|203|         0
#> 13                  90|214|         0
#> 14                  80|220|         0
#> 15                  90|209|         2
#> 16                  60|209|         0
#> 17                  60|209|         0
#> 18                  60|209|         0
#> 19                  60|209|         0
#> 20                  60|209|         2
#> 21                  60|209|         0
#> 22                  60|203|         0
#> 23             80.0001|204|         0
#> 24                  60|206|         0
#> 25                  60|209|         0
#> 26                  60|209|         0
#> 27                  80|220|         0
#> 28                  80|210|         0
#> 29                  60|209|         0
#> 30         80|169.54|211.9|         2
#> 31                  60|209|         0
#> 32                  80|210|         0
#> 33                  80|210|         0
#> 34                  80|212|         0
#> 35                  80|211|         0
#> 36                  80|209|         2
#> 37                  80|206|         2
#> 38                  60|206|         2
#> 39                  80|209|         2
#> 40                  80|212|         2
#> 41                  60|205|         2
#> 42                  80|200|         2
#> 43                  80|205|         2
#> 44                  80|200|         2
#> 45                  90|209|         0
#> 46                  70|209|         0
#> 47             60.0001|209|         0
#> 48     60.0001|213.001|216|         0
#> 49             60.0001|209|         0
#> 50             60.0001|203|         0
#> 51                  68|209|         0
#> 52                  60|200|         0
#> 53             60.0001|209|         0
#> 54             60.0001|209|         0
#> 55                  70|209|         0
#> 56          88|207.404|209|         2
#> 57                  60|206|         2
#> 58                  70|208|         0
#> 59              60|132|214|         2
#> 60                  80|215|         0
#> 61                  60|211|         2
#> 62             60.0001|212|         2
#> 63                  80|208|         2
#> 64                  60|211|         0
#> 65              85|210|215|         2
#> 66    81.446|207.78|217.64|         2
#> 67       85|208.369|219.18|         2
#> 68  89.874|212.449|219.759|         2
#> 69                  85|212|         2
#> 70       90|121.24|150.244|         2
#> 71     88.73|214.84|220.18|         2
#> 72   91.653|207.696|213.54|         0
#> 73                  80|204|         2
#> 74                  80|208|         2
#> 75                 104|218|         2
#> 76                  80|203|         2
#> 77                  80|226|         2
#> 78         26.6667|107.578|         2
#> 79                  80|214|         2
#> 80                  70|203|         2
#> 81                  70|203|         2
#> 82             60.0001|206|         2
#> 83                 140|206|         0
#> 84                  60|223|         2
#> 85             122|208.004|         2
#> 86                  87|212|         2
#> 87                  60|219|         2
#> 88                  70|204|         2
#> 89             60.0001|208|         2
#> 90                  80|212|         2
#> 91              80|212.714|         2
#> 92                 140|208|         2
#> 93                  60|208|         2
#> 94                  80|205|         2
#> 95                  80|212|         2
#> 96             60.0001|214|         2
#> 97                  80|199|         2
#> 98                  70|204|         2
#> 99                  80|209|         0
#> 100                 80|224|         0
#>                                             GL_ArrayMandrels GL_Vdepth
#> 1                                       0|0|0|0|0|0|0|0|0|0|  1807.530
#> 2                      614.3|1118|1422.5|1564.6|0|0|0|0|0|0|  1564.600
#> 3                 167.152|245.913|327.69|373.99|0|0|0|0|0|0|  1227.000
#> 4                    560.9|1123.8|1427.6|1569.6|0|0|0|0|0|0|     0.000
#> 5          193.054|380.384|487.893|584.93|649.657|0|0|0|0|0|  1911.980
#> 6                       543.1|969.3|1235.2|1358|0|0|0|0|0|0|   969.300
#> 7          676.82|1099.42|1444.92|1675.82|1731.22|0|0|0|0|0|  1675.820
#> 8           653.52|980.52|1250.52|1452.52|1596.52|0|0|0|0|0|  1596.520
#> 9                 601.02|906.02|1140.02|1318.02|0|0|0|0|0|0|  1318.020
#> 10                              574|1026|1372|0|0|0|0|0|0|0|  1372.000
#> 11         697.42|1065.52|1357.92|1573.82|1668.12|0|0|0|0|0|  1668.120
#> 12                   616.2|1421.8|1991.6|2288.4|0|0|0|0|0|0|  2288.400
#> 13         667.72|1109.62|1455.02|1685.42|1800.82|0|0|0|0|0|  1800.820
#> 14           565.52|819.02|943.82|1158.82|1249.12|0|0|0|0|0|  1249.100
#> 15                   586.9|1183.7|1732.8|2060.5|0|0|0|0|0|0|     0.000
#> 16                                      0|0|0|0|0|0|0|0|0|0|  1817.300
#> 17                                      0|0|0|0|0|0|0|0|0|0|  1582.000
#> 18                                      0|0|0|0|0|0|0|0|0|0|     0.000
#> 19                                      0|0|0|0|0|0|0|0|0|0|  1613.800
#> 20                           675|1415|2136|2579|0|0|0|0|0|0|  2579.000
#> 21                         546|888|1135|1342|1491|0|0|0|0|0|  1491.000
#> 22                                   1139|0|0|0|0|0|0|0|0|0|   603.500
#> 23                 573.4|987|1375.6|1640.6|1832.8|0|0|0|0|0|  1832.800
#> 24                588.8|1088.8|1367.7|1550|1666.3|0|0|0|0|0|  1367.700
#> 25                539.8|769.3|960.6|1094.2|1189.8|0|0|0|0|0|  1333.500
#> 26           629.299|904.899|1094.6|1228.3|1323.9|0|0|0|0|0|  1323.900
#> 27               784.93|1303.13|1656.63|1876.33|0|0|0|0|0|0|  1876.330
#> 28                539.8|769.3|960.6|1094.2|1189.8|0|0|0|0|0|  1189.800
#> 29                                      0|0|0|0|0|0|0|0|0|0|  1456.400
#> 30                583.9|872.3|1083.72|1246.9|1362|0|0|0|0|0|     0.000
#> 31                                      0|0|0|0|0|0|0|0|0|0|  2138.800
#> 32                                      0|0|0|0|0|0|0|0|0|0|  1108.000
#> 33                                      0|0|0|0|0|0|0|0|0|0|  1098.950
#> 34                                      0|0|0|0|0|0|0|0|0|0|  1507.000
#> 35                                      0|0|0|0|0|0|0|0|0|0|  2350.700
#> 36            324.8|626.31|896.63|1110.51|1258.22|0|0|0|0|0|  1258.220
#> 37                         618|974|1263|1475|1609|0|0|0|0|0|  1609.200
#> 38                         537.7|855.7|1174.7|0|0|0|0|0|0|0|  1174.700
#> 39                         555|899|1247|1802|2108|0|0|0|0|0|  1840.300
#> 40                         539|827|1144|1395|1597|0|0|0|0|0|  1840.300
#> 41                         480.7|885.7|1166.2|0|0|0|0|0|0|0|  1174.700
#> 42                         510|817|1154|1404|1604|0|0|0|0|0|  1840.300
#> 43                         608|965|1253|1455|1600|0|0|0|0|0|  1609.200
#> 44                        633|1260|1579|1743|1840|0|0|0|0|0|  1840.300
#> 45        187.513|298.948|378.287|436.992|480.974|0|0|0|0|0|  1241.100
#> 46                     683.6|1384|1891.4|2044.8|0|0|0|0|0|0|  2030.500
#> 47              637.8|1050.2|1368.5|1599.4|1772.6|0|0|0|0|0|  1772.600
#> 48              647.1|1057.7|1374.9|1634.6|1784.4|0|0|0|0|0|  1635.000
#> 49               928.15|1580.45|2022.22|2319.51|0|0|0|0|0|0|  2406.110
#> 50                        664.9|1327.8|1605.7|0|0|0|0|0|0|0|  1605.700
#> 51                                      0|0|0|0|0|0|0|0|0|0|  1324.700
#> 52                      643.6|969.9|1219|1315.1|0|0|0|0|0|0|  1315.100
#> 53                666|1090.6|1438.1|1697.1|1861.1|0|0|0|0|0|  1438.050
#> 54                666|1090.6|1438.1|1697.1|1861.1|0|0|0|0|0|  1438.050
#> 55                   658.7|1302.8|1848.3|2020.9|0|0|0|0|0|0|  2020.900
#> 56               928.15|1580.45|2022.22|2319.51|0|0|0|0|0|0|     0.000
#> 57                     846.1|1260|1605.8|1864.7|0|0|0|0|0|0|  1864.000
#> 58                           0|0|0|1197.8|1356.57|0|0|0|0|0|  1197.800
#> 59                          398|700|994|1273|1535|0|0|0|0|0|   418.000
#> 60                          590.001|841.001|0|0|0|0|0|0|0|0|   841.000
#> 61                    624.7|866.5|1049.3|1184.2|0|0|0|0|0|0|  1184.000
#> 62                            0|0|0|1203.1|1366.1|0|0|0|0|0|  1366.000
#> 63                    615.6|817.8|1000.9|1126.4|0|0|0|0|0|0|  1126.400
#> 64                                      0|0|0|0|0|0|0|0|0|0|  1420.000
#> 65                      480|826|1173|1511|1840|2159|0|0|0|0|     0.000
#> 66              808.4|1423.9|1834.9|2175.7|2252.5|0|0|0|0|0|     0.000
#> 67                        701.4|1064.7|1168.5|0|0|0|0|0|0|0|     0.000
#> 68               577.7|885.6|1164.5|1346.7|1490.9|0|0|0|0|0|  1346.700
#> 69                          304|546|799|1058|1322|0|0|0|0|0|   284.000
#> 70                  1112.2|1213.2|1647.3|1800.9|0|0|0|0|0|0|     0.000
#> 71                 587.4|904.9|1184.1|1395|1500.6|0|0|0|0|0|     0.000
#> 72                    796|1345|1748.5|2033|2242.9|0|0|0|0|0|  1748.500
#> 73        2514.44|4388.78|5730.31|6075.13|6955.05|0|0|0|0|0|     0.000
#> 74   2207.02|3490.49|4464.24|5214.9|5716.86|5773.62|0|0|0|0|  2207.021
#> 75         1532.15|2408.14|3133.2|3697.51|4501.31|0|0|0|0|0|  4501.310
#> 76                    4206.04|5738.19|6328.74|0|0|0|0|0|0|0|  4206.693
#> 77        2196.52|3480.97|3543.31|4484.91|4547.24|0|0|0|0|0|  5114.830
#> 78              2369.75|5120.08|7206.36|8852.03|0|0|0|0|0|0|  8852.034
#> 79          2144.36|3055.77|3747.7|4250.66|4564.3|0|0|0|0|0|  4250.656
#> 80                                5242.78|0|0|0|0|0|0|0|0|0|  5022.310
#> 81                                5242.78|0|0|0|0|0|0|0|0|0|  5022.310
#> 82                           2454.4|4285.43|0|0|0|0|0|0|0|0|  4284.780
#> 83  1332.02|2109.58|2752.62|3316.93|3792.65|4199.48|0|0|0|0|  4199.480
#> 84                    1751.97|3238.19|4219.49|0|0|0|0|0|0|0|  1286.100
#> 85                                4887.14|0|0|0|0|0|0|0|0|0|  4885.170
#> 86  1512.47|2746.06|3969.82|5193.57|6381.23|7542.65|0|0|0|0|  7542.651
#> 87                    1848.75|2578.41|4063.65|0|0|0|0|0|0|0|  4063.650
#> 88                          2734.91|3523.95|0|0|0|0|0|0|0|0|  3523.620
#> 89                    2432.09|4136.15|5459.97|0|0|0|0|0|0|0|  5774.278
#> 90  915.354|1702.76|2526.25|3382.55|4265.09|5167.32|0|0|0|0|  5167.323
#> 91                          2450.79|3415.35|0|0|0|0|0|0|0|0|  3415.354
#> 92              2309.71|2906.82|3467.85|3986.22|0|0|0|0|0|0|  4199.475
#> 93        1213.91|1981.63|2814.96|3963.25|5019.69|0|0|0|0|0|  5019.685
#> 94        2551.84|4426.18|5548.88|6420.93|6826.77|0|0|0|0|0|  6826.771
#> 95                    3113.19|5289.04|6867.78|0|0|0|0|0|0|0|  7939.305
#> 96        2106.63|3018.37|3710.96|4217.19|4532.48|0|0|0|0|0|  4530.840
#> 97                    2369.09|4073.16|5774.61|0|0|0|0|0|0|0|  5774.278
#> 98              1756.23|2797.24|3649.93|4092.52|0|0|0|0|0|0|     0.000
#> 99        569.976|653.491|824.484|1119.53|1348.13|0|0|0|0|0|  1378.400
#> 100                        569|865|1094|1276|1424|0|0|0|0|0|  1404.000
#>     GL_GSG GL_CO2
#> 1      1.2     65
#> 2      1.2     65
#> 3      1.2     65
#> 4      1.2     65
#> 5      1.2     65
#> 6      1.2     65
#> 7      1.2     65
#> 8      1.2     65
#> 9      1.2     65
#> 10     1.2     65
#> 11     1.2     65
#> 12     1.2     65
#> 13     1.2     65
#> 14     1.2     65
#> 15     1.2     65
#> 16     1.2     65
#> 17     1.2     65
#> 18     1.2     65
#> 19     1.2     65
#> 20     1.2     65
#> 21     1.2     65
#> 22     1.2     65
#> 23     1.2     65
#> 24     1.2     65
#> 25     1.2     65
#> 26     1.2     65
#> 27     1.2     65
#> 28     1.2     65
#> 29     1.2     65
#> 30     1.2     65
#> 31     1.2     65
#> 32     1.2     65
#> 33     1.2     65
#> 34     1.2     65
#> 35     1.2     65
#> 36     1.2     65
#> 37     1.2     65
#> 38     1.2     65
#> 39     0.8     70
#> 40     1.2     65
#> 41     1.2     65
#> 42     1.2     65
#> 43     1.2     65
#> 44     1.2     65
#> 45     1.2     65
#> 46     1.2     65
#> 47     1.2     65
#> 48     1.2     65
#> 49     1.2     70
#> 50     1.2     65
#> 51     1.2     65
#> 52     1.2     65
#> 53     1.2     65
#> 54     1.2     65
#> 55     1.2     65
#> 56     1.2     65
#> 57     1.2     65
#> 58     1.2     65
#> 59     1.2     65
#> 60     1.2     65
#> 61     1.2     65
#> 62     1.2     65
#> 63     1.2     65
#> 64     1.2     65
#> 65     1.2     65
#> 66     1.2     65
#> 67     1.2     65
#> 68     1.2     65
#> 69     1.2     65
#> 70     1.2     65
#> 71     1.2     65
#> 72     1.2     65
#> 73     1.2     65
#> 74     1.2     65
#> 75     1.2     65
#> 76     1.2     65
#> 77     1.2     65
#> 78     1.2     65
#> 79     1.2     65
#> 80     1.2     65
#> 81     1.2     65
#> 82     1.2     65
#> 83     1.2     65
#> 84     1.2     65
#> 85     1.2     65
#> 86     1.2     65
#> 87     1.2     65
#> 88     1.2     65
#> 89     1.2     65
#> 90     1.2     65
#> 91     1.2     65
#> 92     1.2     65
#> 93     1.2     65
#> 94     1.2     65
#> 95     1.2     65
#> 96     1.2     65
#> 97     1.2     65
#> 98     1.2     65
#> 99     1.2     65
#> 100    1.2     65
#>                                                                                                                                                                                                                                                                                                       WT_DATE
#> 1   09/09/2014|02/07/2012|08/08/2012|02/09/2012|03/10/2012|11/11/2012|08/12/2012|13/12/2012|02/01/2013|18/01/2013|03/02/2013|04/03/2013|14/04/2013|21/06/2013|23/07/2013|03/08/2013|22/09/2013|07/10/2013|08/11/2013|08/11/2013|25/01/2014|06/02/2014|09/03/2014|10/06/2014|05/07/2014|06/08/2014|09/09/2014|
#> 2                                                          09/06/2014|21/08/2014|06/02/2012|17/03/2012|11/07/2012|10/08/2012|03/09/2012|05/10/2012|18/11/2012|22/01/2013|11/03/2013|10/04/2013|18/06/2013|04/07/2013|30/07/2013|23/09/2013|14/10/2013|10/11/2013|18/04/2014|21/07/2014|21/08/2014|06/09/2014|
#> 3                                                                                                                                                                                   12/02/2004|04/04/2000|04/05/2000|25/07/2000|01/01/2001|03/02/2001|22/02/2001|02/04/2001|01/06/2001|27/11/2003|12/02/2004|
#> 4                                                                                                                                                  17/02/2014|02/04/2009|22/05/2009|13/06/2009|03/07/2009|01/08/2009|05/09/2009|19/10/2009|23/10/2009|06/11/2009|01/12/2009|13/12/2009|12/07/2011|17/02/2012|
#> 5                                                                                                                                                             06/09/2009|21/09/2009|05/10/2009|02/11/2009|02/12/2009|16/01/2010|07/03/2010|11/07/2008|15/07/2008|24/07/2008|31/07/2008|07/09/2008|03/10/2008|
#> 6                                                                                09/07/2012|10/08/2012|17/09/2012|11/10/2012|11/11/2012|16/01/2013|03/03/2013|15/04/2013|18/06/2013|05/07/2013|03/08/2013|21/09/2013|13/10/2013|23/11/2013|23/11/2013|16/04/2014|19/06/2014|18/08/2014|04/09/2014|09/10/2014|
#> 7                                                                                                                                                                                                                                                                           05/05/2014|13/04/2014|17/12/2013|
#> 8                                                                                                                                                                                                                                                                                      18/08/2014|08/10/2013|
#> 9                                                                                                                                                                                                                                                                                      14/08/2005|21/06/2005|
#> 10                                                                                                                                                                                                                                                                                     12/10/2012|15/09/2012|
#> 11                                                                                                                                                                                                                                                                                     01/06/2005|28/07/1994|
#> 12                                                                                                                                                                                                                                                                          09/06/2011|13/02/2008|21/02/2008|
#> 13                                                                                                                                                                                                                                                                          31/08/2014|06/09/2014|22/06/2014|
#> 14                                                                                                                                                                                                                                                                          15/04/2014|09/07/2008|02/10/2011|
#> 15                                                                                                                                                                                                                                                                                                      41982
#> 16                                                                                                                                                                                                                                                                                                      41642
#> 17                                                                                                                                                                                                                                                                                                      41768
#> 18                                                                                                                                                                                                                                                                                                      41372
#> 19                                                                                                                                                                                                                                                                                                      42065
#> 20                                                                                                                                                                                                                                                                                                      41737
#> 21                                                                                                                                                                       18/01/2014|02/02/2014|03/03/2014|09/04/2014|02/05/2014|13/06/2014|22/07/2014|29/08/2014|30/08/2014|03/10/2014|04/11/2014|01/12/2014|
#> 22                                                                                                                                                                                  17/01/2014|01/02/2014|01/03/2014|02/04/2014|09/05/2014|03/07/2014|26/08/2014|28/08/2014|04/09/2014|07/10/2014|05/11/2014|
#> 23                                                                                                                                                                                                                   12/01/2014|05/03/2014|06/04/2014|11/05/2014|12/06/2014|10/09/2014|04/10/2014|02/12/2014|
#> 24                                                                                                                                                                                                                   23/01/2014|09/02/2014|04/03/2014|12/05/2014|12/05/2014|07/09/2014|05/10/2014|08/03/2015|
#> 25                                                                                                                                                                                                                                                                                     16/09/2014|09/10/2014|
#> 26                                                                                                                                                                                                                                                                                                 15/12/2014
#> 27                                                                                                                                                                                                                                                                          01/12/2005|12/11/2005|31/12/2014|
#> 28                                                                                                                                                                                                                                                                                                 18/05/2014
#> 29                                                                                                                                                                                                                                                                                                 17/03/2015
#> 30                                                                                                                                                                                                                                                                                     12/03/2001|17/07/2000|
#> 31                                                                                                                                                                                                                                                               09/04/2014|19/06/2014|12/09/2014|30/11/2014|
#> 32                                                                                                                                                                                                                                                                                                      41799
#> 33                                                                                                                                                                                                                                                                                                      41799
#> 34                                                                                                                                                                                                                                                                                     02/02/2014|11/03/2014|
#> 35                                                                                                                                                                                                                                                                                                      41918
#> 36                                                                                                                                                                                                        05/10/2014|05/09/2014|04/07/2014|14/06/2014|04/05/2014|18/04/2014|09/04/2014|10/03/2014|19/02/2014|
#> 37                                                                                                                                                                                                                                                                                                      41953
#> 38                                                                                                                                                                                                                                                                          05/09/2014|19/08/2014|03/05/2014|
#> 39                                                                                                                                                                                                                                                                                                      37477
#> 40                                                                                                                                                                                                                                                                                                 14/11/2012
#> 41                                                                                                                                                                                                                                                                                                      41709
#> 42                                                                                                                                                                                                                                                                                                      41800
#> 43                                                                                                                                                                                                                                                                                                      41861
#> 44                                                                                                                                                                                                                                                                                                 31/08/2014
#> 45                                                                                                                                      06/04/2013|18/06/2013|06/07/2013|26/08/2013|16/09/2013|08/11/2013|08/11/2013|08/11/2013|12/04/2014|18/06/2014|21/08/2014|30/08/2014|12/09/2014|22/11/2014|30/12/2014|
#> 46                                                                                                                                                                                                                                                                                               |09/02/2014|
#> 47                                                                                                                                                                                                                                                                                               |24/05/2014|
#> 48                                                                                                                                                                                                                                                                                             |||01/03/2014|
#> 49                                                                                                                                                                       12/09/2003|03/05/2004|08/06/2004|09/03/2005|06/09/2005|07/08/2008|04/10/2008|04/03/2009|06/06/2009|12/12/2010|25/04/2013|17/09/2014|
#> 50                                                                                                                                                                       03/02/1998|11/04/1998|13/09/1998|01/12/1998|03/01/2003|07/07/2005|19/09/2006|30/05/2007|03/06/2008|27/12/2008|10/12/2010|09/07/2014|
#> 51                                                                                                                                                                                  03/10/1998|05/01/2002|01/03/2003|07/04/2005|04/06/2008|23/07/2008|31/10/2008|23/12/2008|19/12/2010|20/01/2014|01/11/2014|
#> 52                                                                                                                                                                                                                                         15/01/2013|08/04/2013|17/06/2013|25/04/2014|30/08/2014|16/09/2014|
#> 53                                                                                                                                                                                                                                                                                              ||06/09/2014|
#> 54                                                                                                                                                                                                                                                                                              ||06/05/2014|
#> 55                                                                                                                                                                                                                                                                                                      41888
#> 56                                                                                                                                                                                                                                                                                                      40727
#> 57                                                                                                                                                                                                                                                    17/07/2012|05/04/2013|27/08/2013|26/07/2013|21/11/2014|
#> 58                                                                                                                                                                                                                                                                                               |29/11/2014|
#> 59                                                                                                                                                                                                                                                                                     29/03/2013|03/11/2014|
#> 60                                                                                                                                                                                                                                                                                               |01/05/2013|
#> 61                                                                                                                                                                                             13/03/1998|06/06/1998|25/09/1998|05/04/2002|01/05/2004|04/01/2005|15/08/2006|09/11/2008|06/09/2010|18/09/2012|
#> 62                                                                                                                                                                                                                                                              11/09/2012|30/10/2013|25/06/2010||29/11/2014|
#> 63                                                                                                                                                                                                                                                                                              ||01/05/2014|
#> 64                                                                                                                                                                                                                                                                                                 28/11/2004
#> 65                                                                                                                                                                                                                                                               15/07/2014|06/08/2014|20/09/2014|24/12/2014|
#> 66                                                                                                                                                                                                                                                                                     18/05/2013|23/12/2014|
#> 67                                                                                                                                                                                                                                                               14/03/2013|20/06/2013|06/06/2014|18/05/2014|
#> 68                                                                                                                                                                                                                                                                          27/07/2013|22/04/2013|04/03/2014|
#> 69                                                                                                                                                                                                                                                                          14/09/2014|22/11/2014|09/12/2014|
#> 70                                                                                                                                                                                                                                                                                                      40673
#> 71                                                                                                                                                                                                                                                                                                 19/10/2011
#> 72                                                                                                                                                                                                                                                                                                      41764
#> 73                                                                                                                                                                                                                                                                          19/09/2014|17/01/2015|17/01/2015|
#> 74                                                                                                                                                                                                                                                                                     06/04/2014|31/12/2014|
#> 75                                                                                                                                                                                                                              21/11/2013|15/04/2014|04/05/2014|12/06/2014|15/04/2014|15/01/2015|15/01/2015|
#> 76                                                                                                                                                                                                                                                                          06/06/2014|27/01/2015|27/01/2015|
#> 77                                                                                                                                                                                             29/01/2013|12/02/2013|13/03/2013|25/09/2013|20/10/2013|11/03/2013|18/05/2014|16/07/2014|18/05/2914|02/01/2015|
#> 78                                                                                                                                                                                                                  |25/09/2013|19/07/2013|15/06/2014|15/06/2014|11/07/2014|12/05/2014|24/01/2015|24/01/2015|
#> 79                                                                                                                                                                                                                                                                                    |19/09/2014|19/09/2014|
#> 80                                                                                                                                                                                                                                                                                                       <NA>
#> 81                                                                                                                                                                                                                                                                                                       <NA>
#> 82                                                                                                                                                                                                                                                                                                      42005
#> 83                                                                                                                                                                                                                   08/08/2012|15/09/2012|09/10/2012|20/06/2012|30/07/2012|18/04/2014|21/05/2014|14/06/2014|
#> 84                                                                                                                                                                                                                                                                          05/01/2014|16/06/2014|23/12/2014|
#> 85                                                                                                                                                                                                       |22/09/2013|17/10/2013|18/04/2014|21/05/2014|10/06/2014|10/06/2014|13/07/2014|20/01/2015|20/01/2015|
#> 86                                                                                                                                                                                                                   24/09/2013|11/11/2013|08/03/2014|13/04/2014|16/06/2014|16/06/2014|16/07/2014|18/12/2014|
#> 87                                                                                                                                                                                                                                         19/03/2013|05/05/2014|07/07/2014|17/09/2014|18/01/2015|18/01/2015|
#> 88                                                                                                                                                                                                                                                               31/10/2012|19/11/2012|29/01/2013|23/04/2013|
#> 89                                                                                                                                                                                                                                                                          14/06/2014|17/01/2015|17/01/2015|
#> 90                                                                                                                                                                                                                                                               14/06/2014|21/05/2014|20/01/2015|20/01/2015|
#> 91                                                                                                                                                                                                                                         18/04/2014|09/07/2014|09/07/2014|24/02/2014|18/01/2015|18/01/2015|
#> 92                                                                                                                                                                                                        08/08/2012|15/09/2012|09/10/2012|20/06/2012|30/07/2012|21/05/2014|05/06/2014|05/06/2014|05/07/2014|
#> 93                                                                                                                                                                                                                                                               14/04/2014|21/05/2014|10/06/2014|10/06/2014|
#> 94                                                                                                                                                                                                                              19/02/2009|23/09/2013|10/04/2013|23/11/2013|07/03/2014|07/03/2014|18/12/2014|
#> 95                                                                                                                                                                                                                  |29/01/2013|01/03/2013|15/03/2013|21/07/2013|14/07/2014|31/08/2014|24/01/2015|24/01/2015|
#> 96                                                                                                                                                                                                                                                                         |16/06/2013|06/07/2014|17/01/2015|
#> 97                                                                                                                                                                                                                                                                          06/06/2014|06/06/2014|16/09/2014|
#> 98                                                                                                                                                                                                                                                                                               |15/06/2013|
#> 99                                                                                          31/08/2014|30/06/2012|01/09/2012|08/09/2012|01/10/2012|04/10/2012|11/11/2012|16/01/2013|04/02/2013|03/03/2013|11/04/2013|18/05/2013|20/06/2013|13/07/2013|23/08/2013|09/11/2013|23/06/2014|17/07/2014|31/08/2014|
#> 100                                                                                                                                                                                                                                                                                    07/09/2014|13/07/2014|
#>                                                                                                           WT_THT
#> 1   121|112|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|
#> 2                       125|125|125|125|135|125|125|127|125|125|125|125|125|125|125|125|125|125|125|125|125|122|
#> 3                                                                             96|99|99|99|99|99|99|99|99|124|99|
#> 4                                                       108|108|108|108|108|108|108|108|108|108|108|108|108|108|
#> 5                                                           190|192|190|190|190|188|145|190|190|190|190|190|192|
#> 6                               125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|152|125|125|125|
#> 7                                                                                                 125.6|125|125|
#> 8                                                                                                       125|125|
#> 9                                                                                                       110|113|
#> 10                                                                                                      131|145|
#> 11                                                                                                      104|150|
#> 12                                                                                                  110|145|114|
#> 13                                                                                            163.4|127.4|111.2|
#> 14                                                                                                170|143.6|177|
#> 15                                                                                                           122
#> 16                                                                                                           100
#> 17                                                                                                            60
#> 18                                                                                                           120
#> 19                                                                                                           105
#> 20                                                                                                            91
#> 21                                        198.5|198.5|198.5|197.6|197.6|266|197.6|197.6|197.6|197.6|197.6|197.6|
#> 22                                                                             68|72|70|78|72|68|78|78|70|67|93|
#> 23                                                                              176|176|176|176|176|176|176|155|
#> 24                                                                                    80|80|80|80|130|80|80|142|
#> 25                                                                                                      120|120|
#> 26                                                                                                           153
#> 27                                                                                                  155|138|136|
#> 28                                                                                                           160
#> 29                                                                                                           100
#> 30                                                                                                       110|96|
#> 31                                                                                              200|200|100|120|
#> 32                                                                                                           152
#> 33                                                                                                           152
#> 34                                                                                                      121|116|
#> 35                                                                                                           147
#> 36                                                                          160|170|170|170|170|170|170|170|170|
#> 37                                                                                                           127
#> 38                                                                                                  150|152|158|
#> 39                                                                                                           165
#> 40                                                                                                           155
#> 41                                                                                                           139
#> 42                                                                                                           130
#> 43                                                                                                           106
#> 44                                                                                                           103
#> 45                                                  120|120|120|120|120|120|120|120|120|120|120|120|120|120|153|
#> 46                                                                                                      130|114|
#> 47                                                                                                      168|115|
#> 48                                                                                            158|170.6|176|140|
#> 49                                                   70|72|72|60.0001|62.0001|70|72|72|66.9999|326.12|150.8|130|
#> 50                                                            140|140|140|140|140|140|140|140|140|140|277.52|99|
#> 51                                                               158|158|158|158|158|158|158|158|309.92|150|140|
#> 52                                                                                176|176|105.8|138.2|138.2|137|
#> 53                                                                                                176|165.2|155|
#> 54                                                                                                176|165.2|133|
#> 55                                                                                                           135
#> 56                                                                                                           140
#> 57                                                                                      140|113|132.8|132.8|110|
#> 58                                                                                                      161|120|
#> 59                                                                                                    135|170.6|
#> 60                                                                                                      110|105|
#> 61                                                                      176|176|176|176|176|176|176|176|185|130|
#> 62                                                                                      176|165.2|176|172.4|145|
#> 63                                                                                              181.4|172.4|150|
#> 64                                                                                                           149
#> 65                                                                                              150|150|150|143|
#> 66                                                                                                      165|135|
#> 67                                                                                              102|109|109|115|
#> 68                                                                                                  162|176|153|
#> 69                                                                                                  145|135|135|
#> 70                                                                                                         116.5
#> 71                                                                                                           155
#> 72                                                                                                           115
#> 73                                                                                              104|186.8|102.2|
#> 74                                                                                                   87.8|116.6|
#> 75                                                                              114.8|149|149|141|110|154.4|140|
#> 76                                                                                                 93|165.2|125|
#> 77                                                        172.4|158|172.4|203|179.6|192.2|159.8|145.4|140|116.6|
#> 78                                                                         30.5556|55|49|59|44|45|40.5556|41|42|
#> 79                                                                                                  87|176|98.6|
#> 80                                                                                                           138
#> 81                                                                                                           138
#> 82                                                                                                 109.400009155
#> 83                                                                  123.8|134.6|131|123.8|123.8|136.4|168.8|149|
#> 84                                                                                                  120|84|89.6|
#> 85                                                          158|158|158|165.2|141.8|161.6|141.8|141.8|172.4|131|
#> 86                                                                              52|69|68|73|152.6|116.6|167|122|
#> 87                                                                          143.6|172.4|127.4|179.6|190.4|141.8|
#> 88                                                                                        183.2|190.4|179.6|130|
#> 89                                                                                               95|116.96|89.6|
#> 90                                                                                              104|98.6|140|95|
#> 91                                                                                185|172.4|122|87.5|190.4|98.6|
#> 92                                                              123.8|134.6|131|123.8|123.8|145.4|194|183.2|194|
#> 93                                                                                        190.4|158|181.4|136.4|
#> 94                                                                          163.4|141.8|140|100|163.4|113|105.8|
#> 95                                                                 87.0001|145.4|145.4|149|156.2|104|104|0|84.2|
#> 96                                                                                      87.0001|179.6|125|147.2|
#> 97                                                                                                185|133|188.6|
#> 98                                                                                                64.9999|113.8|
#> 99                                  125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|125|
#> 100                                                                                                     125|143|
#>                                                                                                                                                               WT_LIQRT
#> 1   561.2|384.5|365.8|405.3|312.2|501.1|469.9|551.1|887.2|534.7|474.2|408.7|527.2|266.9|377.8|540.6|462.5|540.2|540.9|541.1|546.8|559.2|559.2|561.1|559.6|559.3|561.2|
#> 2                                     560|528|711.2|790.6|973.7|732.4|402.5|747.8|793.5|958.9|1190.5|1135.3|909.1|1006.4|980|1013.9|550.6|551.7|591.3|528.3|528.3|560|
#> 3                                                                                                          382.6|1296|862|739.6|486|1247|208.6|505.8|345.1|1327|382.6|
#> 4                                                                                     150.8|93.9|257.8|213.5|255.1|246.9|218.2|48.4|56.6|96.7|281.2|109.8|127.9|150.8|
#> 5                                                                             1369.3|1244.9|1035.3|1049.9|1104.3|961.7|1290.3|1911.8|1187.8|2578.1|2369|1831.3|1544.3|
#> 6                                         1108.8|1440.4|1400.6|543.5|1417.3|676.6|1228.9|479.7|1050.2|1431.1|528|1399.7|553.5|555|555.3|1448|1344.6|557.4|559.7|558.9|
#> 7                                                                                                                                                         560|558|558|
#> 8                                                                                                                                                         560.4|558.5|
#> 9                                                                                                                                                        440.8|1722.5|
#> 10                                                                                                                                                        402.7|718.1|
#> 11                                                                                                                                                          345.9|731|
#> 12                                                                                                                                                 257.6|2376.8|453.5|
#> 13                                                                                                                                                  217.4|559.7|197.5|
#> 14                                                                                                                                                1503.9|602.5|2131.5|
#> 15                                                                                                                                                       558.900024414
#> 16                                                                                                                                                                 589
#> 17                                                                                                                                                                 560
#> 18                                                                                                                                                                 531
#> 19                                                                                                                                                       564.599975586
#> 20                                                                                                                                                               558.5
#> 21                                                                                                                    499|492|412|439|452|123|467|421|425|705|708|647|
#> 22                                                                                                                        416|521|452|595|443|458|574|542|514|428|568|
#> 23                                                                                                                            1806|1775|1781|1890|1080|2336|1900|1873|
#> 24                                                                                                                             1518|1415|1418|1491|1491|1728|802|1649|
#> 25                                                                                                                                                       1039|867.352|
#> 26                                                                                                                                                                1618
#> 27                                                                                                                                                1795.9|1141.3|895.8|
#> 28                                                                                                                                                      1477.099975586
#> 29                                                                                                                                                                 863
#> 30                                                                                                                                                        527.7|210.4|
#> 31                                                                                                                                                   1674|746|392|904|
#> 32                                                                                                                                                                1730
#> 33                                                                                                                                                                1730
#> 34                                                                                                                                                            493|397|
#> 35                                                                                                                                                                1634
#> 36                                                                                              2420.77|2378.36|2279.2|2190.34|2631.1|2773.33|3828.28|2972.53|3648.22|
#> 37                                                                                                                                                                 753
#> 38                                                                                                                                                     2034|1923|1952|
#> 39                                                                                                                                                                1944
#> 40                                                                                                                                                                1393
#> 41                                                                                                                                                                1369
#> 42                                                                                                                                                      1082.199951172
#> 43                                                                                                                                                                 485
#> 44                                                                                                                                                       314.700012207
#> 45                                                                      1782.8|1197.9|1175.4|1586.8|1175.4|1174|1824|1805.4|133.7|772.9|1000.8|1000|1220.9|888.4|1342|
#> 46                                                                                                                                                            968|580|
#> 47                                                                                                                                                         900|714.76|
#> 48                                                                                                                                                 900|1290|1347|1155|
#> 49                                                                                                             854|986|898|575|711|960|993|874|854|1273.2|997.56|1347|
#> 50                                                                           817.675|817.675|729.618|817.675|251.592|251.592|377.389|345.94|478.026|345.94|980.95|595|
#> 51                                                                                   1572.45|220.143|943.472|628.981|251.592|691.879|503.185|440.287|1374.39|518|1207|
#> 52                                                                                                                                        1160|631|508|1390|1202|1364|
#> 53                                                                                                                                                      1057|776|1932|
#> 54                                                                                                                                                      1057|776|1065|
#> 55                                                                                                                                                                1364
#> 56                                                                                                                                                      1192.199951172
#> 57                                                                                                                                          900|814.8|607.5|683.4|700|
#> 58                                                                                                                                                            721|898|
#> 59                                                                                                                                                         457|2113.7|
#> 60                                                                                                                                                            335|331|
#> 61                                                                                          314.491|786.226|754.777|679.3|817.675|503.185|415.128|1886.94|2066.12|858|
#> 62                                                                                                                                         1484|1923|2586|1200|1674.1|
#> 63                                                                                                                                                     1093|1532|1250|
#> 64                                                                                                                                                                 596
#> 65                                                                                                                                        2523.6|2437.2|2473.4|1891.1|
#> 66                                                                                                                                                      2253.2|1179.3|
#> 67                                                                                                                                                214.7|288.4|391|388|
#> 68                                                                                                                                                 1421.1|215.9|966.6|
#> 69                                                                                                                                               1420.9|1074.3|1141.6|
#> 70                                                                                                                                                      1799.199951172
#> 71                                                                                                                                                      1166.800048828
#> 72                                                                                                                                                       416.100006104
#> 73                                                                                                                                                        491|330|330|
#> 74                                                                                                                                                          397|763.6|
#> 75                                                                                                                                339|1261|687|1075|212|1159.1|1159.1|
#> 76                                                                                                                                                    274.5|1004|1004|
#> 77                                                                                                         2469.36|821.16|1337.4|581|1208|689|4116|1093|1307.16|507.1|
#> 78                                                                                                                               1142|350|263|455|455|529|369|362|362|
#> 79                                                                                                                                                       1142|286|286|
#> 80                                                                                                                                                                1142
#> 81                                                                                                                                                                1142
#> 82                                                                                                                                                      1082.199951172
#> 83                                                                                                                          284.1|150.6|231.6|69.84|69.84|279|195|396|
#> 84                                                                                                                                                      847|270|317.8|
#> 85                                                                                                                          770|1500|1400|137|387|613|613|711|200|200|
#> 86                                                                                                                                    656|880|953|484|658|658|353|556|
#> 87                                                                                                                                 594.72|1037.9|864|1261.9|1143|1143|
#> 88                                                                                                                                                   505|755|2418|859|
#> 89                                                                                                                                                    492|383.2|383.2|
#> 90                                                                                                                                                    396|243|267|267|
#> 91                                                                                                                                            326|650|650|439|250|250|
#> 92                                                                                                                  284.1|150.6|231.6|69.84|69.84|2365|2398|2398|2166|
#> 93                                                                                                                                                1975|1413|1634|1634|
#> 94                                                                                                                                       1518|951|543|515|814|814|359|
#> 95                                                                                                                            1142|882|674.52|615|611|672|889|100|100|
#> 96                                                                                                                                              1142|1482|1021.3|1664|
#> 97                                                                                                                                                   1087|1087|1353.8|
#> 98                                                                                                                                                            585|553|
#> 99                                                        560|496.1|603.9|601.2|709.2|687.4|699.4|609.7|396.9|528.8|577|642.4|564.6|738.2|753.5|555|378.3|558.5|560.8|
#> 100                                                                                                                                                        784.6|1200|
#>                                                                                                                                                  WT_WC
#> 1   65|66.9|71.08|71.09|75.96|71.1|71.09|68.66|71.1|63.42|71.09|71.08|71.08|26.04|71.09|71.09|71.08|31.1|31.06|31.13|51.31|28.09|28.09|50|50|50|65.03|
#> 2                           70|68|65.94|80.83|75.97|74.75|75.96|75.97|73.09|77.8|76.95|76.94|61.26|75.97|71.09|71.09|71.11|71.1|67.31|68.5|68.5|70.01|
#> 3                                                                                                              0|0|0.01|0|0.05|0|3.02|27.98|17.06|0|0|
#> 4                                                                                                        5|0|20.36|0|0|0|3.46|0|0|0|9.26|0|15.94|5.01|
#> 5                                                                          95.13|92|90.46|90.46|92.83|90.46|95.19|71.14|88.69|60.59|75.74|90.46|90.46|
#> 6                                80.64|71.09|85.66|80.83|99.85|90.46|97.66|85.66|80.82|95.24|84.89|90.46|80.84|80.83|80.86|80|80.01|79.89|79.97|80.01|
#> 7                                                                                                                                            90|90|90|
#> 8                                                                                                                                               95|95|
#> 9                                                                                                                                               90|95|
#> 10                                                                                                                                              90|90|
#> 11                                                                                                                                               90|0|
#> 12                                                                                                                                             56|0|0|
#> 13                                                                                                                                           90|95|90|
#> 14                                                                                                                                        90|74|87.37|
#> 15                                                                                                                                                  60
#> 16                                                                                                                                        76.199996948
#> 17                                                                                                                                        90.029998779
#> 18                                                                                                                                                   0
#> 19                                                                                                                                        89.970001221
#> 20                                                                                                                                                  80
#> 21                                                                                                                49|50|50|50|52|29|53|51|49|45|55|49|
#> 22                                                                                                                             0|0|0|5|5|7|8|10|8|7|8|
#> 23                                                                                                                        64.3|62|62|61|61|79|70.8|70|
#> 24                                                                                                                         77|83|88|88|89|90|86|73.84|
#> 25                                                                                                                                            92|92.5|
#> 26                                                                                                                                                89.5
#> 27                                                                                                                                           90|90|95|
#> 28                                                                                                                                                  90
#> 29                                                                                                                                         2.779999971
#> 30                                                                                                                                         5.08|53.82|
#> 31                                                                                                                                        85|88|88|95|
#> 32                                                                                                                                                  79
#> 33                                                                                                                                                  79
#> 34                                                                                                                                              81|90|
#> 35                                                                                                                                                  71
#> 36                                                                                                           70|75.975|60.873|48.923|45|45|44|9|8.999|
#> 37                                                                                                                                                  80
#> 38                                                                                                                                   44.835|48.741|86|
#> 39                                                                                                                                                   0
#> 40                                                                                                                                                  88
#> 41                                                                                                                                                  70
#> 42                                                                                                                                                21.5
#> 43                                                                                                                                                  54
#> 44                                                                                                                                        91.199996948
#> 45                                                                      90.45|85.89|85.64|80.83|85.64|85.69|79.99|80.83|79.94|83.34|80|80|85.01|80|80|
#> 46                                                                                                                                              85|80|
#> 47                                                                                                                                              85|85|
#> 48                                                                                                                                        94|80|80|90|
#> 49                                                                                                          60|70|60|50|60|54|56|50|50|59.19|90.01|85|
#> 50                                                                                                                 0|0|0|0|20|50|65|80|50|60|34.72|40|
#> 51                                                                                                                 0|18|19|10|70|55|30|10|15.38|80|85|
#> 52                                                                                                                               82.82|80|80|85|80|80|
#> 53                                                                                                                                           87|90|95|
#> 54                                                                                                                                           87|90|95|
#> 55                                                                                                                                                  51
#> 56                                                                                                                                        60.270000458
#> 57                                                                                                                                     70|80|80|80|80|
#> 58                                                                                                                                              20|35|
#> 59                                                                                                                                              42|50|
#> 60                                                                                                                                              70|60|
#> 61                                                                                                                     0|0|20|50|50|50|50|80|80.01|90|
#> 62                                                                                                                                     72|60|55|50|50|
#> 63                                                                                                                                           56|70|70|
#> 64                                                                                                                                                  50
#> 65                                                                                                                                     30|29.99|30|30|
#> 66                                                                                                                                              60|60|
#> 67                                                                                                                                     10|39.95|20|40|
#> 68                                                                                                                                        90.47|95|90|
#> 69                                                                                                                                        80|80.01|80|
#> 70                                                                                                                                        85.620002747
#> 71                                                                                                                                        90.449996948
#> 72                                                                                                                                        35.029998779
#> 73                                                                                                                                           85|85|85|
#> 74                                                                                                                                            5|18.83|
#> 75                                                                                                                               2|0.9|14|0|2|4.9|4.9|
#> 76                                                                                                                                           20|60|60|
#> 77                                                                                                                 86.7|75|80|75|73|82|92|56|54|50.76|
#> 78                                                                                                                         89|55|50|60|60|23|59|44|44|
#> 79                                                                                                                                           89|51|51|
#> 80                                                                                                                                                  89
#> 81                                                                                                                                                  89
#> 82                                                                                                                                        50.689998627
#> 83                                                                                                                                 0|0|0|0|0|19|20|17|
#> 84                                                                                                                                           64|62|62|
#> 85                                                                                                                      75|90|90|63|41|63|63|51|62|62|
#> 86                                                                                                                            70|20|64|54|52|52|44|54|
#> 87                                                                                                                         69.14|61.73|69|77.12|78|78|
#> 88                                                                                                                                        88|91|85|96|
#> 89                                                                                                                                     47|63.51|63.51|
#> 90                                                                                                                                        17|20|18|18|
#> 91                                                                                                                                  61|66|66|38|69|69|
#> 92                                                                                                                              0|0|0|0|0|74|71|71|70|
#> 93                                                                                                                                        40|69|71|71|
#> 94                                                                                                                               65|60|60|68|60|60|52|
#> 95                                                                                                                      89|60|60|93.92|70|57|75|75|75|
#> 96                                                                                                                                  89|72|52.13|64.89|
#> 97                                                                                                                                        52|52|50.77|
#> 98                                                                                                                                              90|95|
#> 99                                       89.6|85.23|84.36|71.09|85.45|85.66|84.22|87.19|83.5|83.01|83.23|84.06|85.28|86.34|85.64|80.83|90.02|90|89.97|
#> 100                                                                                                                                             80|80|
#>                                                                                                                                                 WT_THP
#> 1   246.5|232.1|246.6|217.6|246.6|217.6|217.6|203|203|203|232.1|232.1|232.1|232.1|261.1|217.6|246.6|232.1|232|232.1|232.1|232|217.5|203|203|232|246.5|
#> 2                            246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 3                                                                                                 435|304.5|348|348|334|334|304.5|334|304.5|290|435.1|
#> 4                                                                 362.6|464.1|507.6|507.6|319.1|304.6|290.1|304.6|304.6|304.6|290.1|319.1|391.6|362.6|
#> 5                                                                       261.1|217.6|246.6|232.1|232.1|217.6|261.1|217.6|261.1|217.6|246.6|246.6|217.6|
#> 6                                   304.6|362.6|304.6|348.1|319.1|290.1|246.6|261.1|290.1|333.6|362.6|304.6|261.1|275.6|275.5|319|333.5|188.5|319|290|
#> 7                                                                                                                                         261|290|290|
#> 8                                                                                                                                           250|232.2|
#> 9                                                                                                                                         290.1|101.5|
#> 10                                                                                                                                        246.6|377.1|
#> 11                                                                                                                                            250|674|
#> 12                                                                                                                                  246.6|246.6|217.6|
#> 13                                                                                                                                      232|232|333.5|
#> 14                                                                                                                                 304.5|290.1|267.18|
#> 15                                                                                                                                       261.000000854
#> 16                                                                                                                                               362.5
#> 17                                                                                                                                                 290
#> 18                                                                                                                                       348.100006104
#> 19                                                                                                                                               304.5
#> 20                                                                                                                                                 232
#> 21                                                    217.696|232.696|217.696|203.696|232.696|232.696|246.696|232.696|203.696|188.696|145.696|130.696|
#> 22                                                                                                     101.5|101.53|101.5|261|87|80|87|101.5|87|87|87|
#> 23                                                                                    188.696|203.696|203.696|246.696|232.696|174.696|203.696|159.696|
#> 24                                                                                                                  160|247|247|247|243|261|247|217.5|
#> 25                                                                                                                                            218|218|
#> 26                                                                                                                                       217.500000854
#> 27                                                                                                                                  101.5|188.5|246.5|
#> 28                                                                                                                                               130.5
#> 29                                                                                                                                       130.199996948
#> 30                                                                                                                                          101.5|102|
#> 31                                                                                                                      261.696|203.696|275.696|130.5|
#> 32                                                                                                                                                 232
#> 33                                                                                                                                                 232
#> 34                                                                                                                                             102|87|
#> 35                                                                                                                                                 160
#> 36                                                                                                  217.557|203.053|261|290|261|275.5|261|217.5|246.5|
#> 37                                                                                                                                                  87
#> 38                                                                                                                                        203|203|203|
#> 39                                                                                                                                                 290
#> 40                                                                                                                                                 160
#> 41                                                                                                                                                 116
#> 42                                                                                                                                               188.5
#> 43                                                                                                                                                  87
#> 44                                                                                                                                               159.5
#> 45                                                                    217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 46                                                                                                                                          239|188.6|
#> 47                                                                                                                                            203|200|
#> 48                                                                                                                                  217|246|304|214.3|
#> 49                                                                    231.999|218|276|174|333.999|188.999|188.999|160.001|160.001|156.541|290.154|276|
#> 50                                                      261.068|261.068|304.579|159.542|203.053|174.045|174.045|145.038|159.542|130.534|130.53|217.56|
#> 51                                                                    304.772|275.764|232.253|174.238|188.741|174.238|174.238|159.734|203.247|207|218|
#> 52                                                                                                              275.764|217.749|232.253|188.5|218|218|
#> 53                                                                                                                                      195|246.5|290|
#> 54                                                                                                                                    195|246.5|214.3|
#> 55                                                                                                                                                 261
#> 56                                                                                                                                       159.500000854
#> 57                                                                                                                     174|261.07|261.07|261.07|217.6|
#> 58                                                                                                                                            246|261|
#> 59                                                                                                                                            188|275|
#> 60                                                                                                                                            232|233|
#> 61                                                                         275.572|145.038|145.038|348.091|217.557|159.542|159.542|275.572|268.32|290|
#> 62                                                                                                                              275|290|232|246.5|261|
#> 63                                                                                                                                        203|261|377|
#> 64                                                                                                                                                 261
#> 65                                                                                                                                  203|203|217.6|261|
#> 66                                                                                                                                          246.6|232|
#> 67                                                                                                                                124.9|188.6|232|214|
#> 68                                                                                                                                    188.6|217.6|203|
#> 69                                                                                                                                  217.6|217.6|217.5|
#> 70                                                                                                                                       203.100006958
#> 71                                                                                                                                       217.600006958
#> 72                                                                                                                                               188.5
#> 73                                                                                                                            327.696|245.696|245.696|
#> 74                                                                                                                                         100|80.696|
#> 75                                                                                            173.696|214.696|188.696|246.696|269.696|217.696|217.696|
#> 76                                                                                                                              174.696|429.396|417.5|
#> 77                                                                                              261.138|261.138|275.641|232|203|232|203|305|232|195.7|
#> 78                                                                                                     159.304|261|232|174|174|208|143.67|265.2|265.2|
#> 79                                                                                                                                174|119.696|119.696|
#> 80                                                                                                                                       174.000000854
#> 81                                                                                                                                       174.000000854
#> 82                                                                                                                                       122.395996948
#> 83                                                                                         174.24|156.84|159.74|174.24|174.24|213.346|171.839|246.696|
#> 84                                                                                                                              194.304|188.304|195.6|
#> 85                                                                                174|261|275|246.696|228.696|217.696|217.696|207.696|304.696|304.696|
#> 86                                                                                    275.696|231.696|377.696|203.696|231.696|231.696|231.696|281.696|
#> 87                                                                                                                217.798|193|249|174|246.696|246.696|
#> 88                                                                                                                                    159|130|246|203|
#> 89                                                                                                                            217.696|217.596|217.596|
#> 90                                                                                                                            232|160|232.196|232.196|
#> 91                                                                                                    214.696|191.696|191.696|152.696|246.696|246.696|
#> 92                                                                                 174.24|156.84|159.74|174.24|174.24|275.696|289.696|289.696|246.696|
#> 93                                                                                                                    214.696|275.696|173.696|173.696|
#> 94                                                                                            289.696|318.696|449.696|304.696|285.696|285.696|303.296|
#> 95                                                                                    174|319.355|319.355|275.834|218|203.696|239.446|259.196|259.196|
#> 96                                                                                                                                174|218|203|250.896|
#> 97                                                                                                                            333.696|333.696|275.696|
#> 98                                                                                                                                        144.696|449|
#> 99                                        319|246.6|261.1|261.1|261.1|261.1|246.6|290.1|290.1|290.1|261.1|290.1|290.1|348.1|319.1|275.6|275.5|261|319|
#> 100                                                                                                                                           290|522|
#>                                                                                                                                              WT_GOR
#> 1          3145|1449|2108|2496|4214|4672|3689|3688|4216|542.6|426|4215|4214|460.4|4216|4216|4215|2243|1874|1166|1737|1468|1741|2352|2609|2599|3145|
#> 2   4160|3974|1624.7|336.5|1581.5|287.5|1581|1581.8|1053|1265.5|1265.9|1160.1|759.6|1160.2|1160.1|1632.6|2974.1|4081.5|1759.7|3974.1|3974.1|3831.9|
#> 3                                                                                         453|573.5|4186|2976|952.7|1848|1347|1227|1015|1235|453.1|
#> 4                                       4867|46172.6|17401.8|16889.5|13548.2|13622.8|16676.7|85862.6|66214.7|59297.7|12641.8|31426.3|5126.4|4867.5|
#> 5                                                                            869|1800|43.9|2963|415.4|1800|411.3|273.7|322.3|267.9|43.4|1870.4|450|
#> 6                  1476.3|1371|1265.8|1266|1573.4|1686.4|1794.5|1792.9|600.5|1792|1792.3|3188.6|5614.4|6910.6|6990.9|967.8|2789|5802|6528.4|6727.8|
#> 7                                                                                                                                   1233|1472|3676|
#> 8                                                                                                                                         544|3570|
#> 9                                                                                                                                        4735|4382|
#> 10                                                                                                                                       4747|3804|
#> 11                                                                                                                                       1127|1136|
#> 12                                                                                                                               593|413.55|413.55|
#> 13                                                                                                                             6892.6|1354|10697.9|
#> 14                                                                                                                             1398.21|486.59|1923|
#> 15                                                                                                                                   2615.699951172
#> 16                                                                                                                                             4140
#> 17                                                                                                                                             7727
#> 18                                                                                                                                    413.100006104
#> 19                                                                                                                                   2103.600097656
#> 20                                                                                                                                             4000
#> 21                                                                                      2214|2214|2101|2101|2301|1383|2093|2215|2159|1771|2000|512|
#> 22                                                                                                     696|554|645|421|614|398|458|652|186|534|557|
#> 23                                                                                                                 689|847|639|639|356|227|441|634|
#> 24                                                                                                           1108|2230|1051|2501|2705|272|642|2700|
#> 25                                                                                                                                        2308|697|
#> 26                                                                                                                                              845
#> 27                                                                                                                                    514|995|2462|
#> 28                                                                                                                                             1579
#> 29                                                                                                                                              415
#> 30                                                                                                                                        977|1500|
#> 31                                                                                                                             1251|5023|9526|6000|
#> 32                                                                                                                                             1597
#> 33                                                                                                                                             1839
#> 34                                                                                                                                       7904|7501|
#> 35                                                                                                                                              952
#> 36                                                                                     1464.07|2479.11|1334.41|1073.61|6001|6001|6001|6000.96|6001|
#> 37                                                                                                                                             1139
#> 38                                                                                                                                    773|849|5301|
#> 39                                                                                                                                             9003
#> 40                                                                                                                                             1582
#> 41                                                                                                                                              500
#> 42                                                                                                                                              426
#> 43                                                                                                                                              552
#> 44                                                                                                                                              732
#> 45                                            5763.4|2132.7|1532.9|718.3|2392.9|5214.8|2466.9|1462.2|3358|5126.2|1090.9|3321.9|583.3|1254.6|1435.2|
#> 46                                                                                                                                        375|3108|
#> 47                                                                                                                                       1200|1772|
#> 48                                                                                                                            5000|5800|11000|7443|
#> 49                                                                                      568|1161|657|418|427|916|1036|500|782|1058.29|4872.07|1654|
#> 50                                                  395.034|395.034|395.034|395.034|395.034|395.034|395.034|395.034|395.034|395.034|405.49|596.134|
#> 51                                                                    395.034|395.034|395.034|395.034|395.034|395.034|395.034|395.034|842|415|1714|
#> 52                                                                                                                     3406|7760|9052|1050|916|807|
#> 53                                                                                                                                  1600|2000|3804|
#> 54                                                                                                                                 1600|2000|10424|
#> 55                                                                                                                                             1719
#> 56                                                                                                                                   1114.900024414
#> 57                                                                                                                      2000|500|10003.8|7500|1716|
#> 58                                                                                                                                        2000|675|
#> 59                                                                                                                                        1500|426|
#> 60                                                                                                                                         500|500|
#> 61                                                                        395.034|395.034|395.034|395.034|395.034|395.034|395.034|395.034|1000|426|
#> 62                                                                                                                            1500|900|631|631|415|
#> 63                                                                                                                                   2500|1300|600|
#> 64                                                                                                                                              702
#> 65                                                                                                                             53.9|55.8|363.9|404|
#> 66                                                                                                                                     2368.52|762|
#> 67                                                                                                                             2564|1268.6|420|420|
#> 68                                                                                                                                2098.8|0|10631.6|
#> 69                                                                                                                              1530|1469.3|1625.9|
#> 70                                                                                                                                             2958
#> 71                                                                                                                                    674.539978027
#> 72                                                                                                                                   1779.199951172
#> 73                                                                                                                                     500|500|500|
#> 74                                                                                                                                         720|720|
#> 75                                                                                                                    2626|586|950|700|500|660|500|
#> 76                                                                                                                                  1000|2674|2674|
#> 77                                                                                          1921.27|2925.87|3098.74|388|1123|2034|2801|934|455|530|
#> 78                                                                                                        9001|3129|2827|2635|611|364|550|6247|940|
#> 79                                                                                                                                    9001|540|530|
#> 80                                                                                                                                             9001
#> 81                                                                                                                                             9001
#> 82                                                                                                                                              850
#> 83                                                                                                    2625|2958|2625|3217.56|3378.56|860|14012|500|
#> 84                                                                                                                                     450|530|530|
#> 85                                                                                                     820|5200|5200|873|305|1080|505|1080|658|658|
#> 86                                                                                                              1050|1800|837|112|159|500|5056|667|
#> 87                                                                                                                      802.84|530|567|530|537|573|
#> 88                                                                                                                             1259|1261|1260|1259|
#> 89                                                                                                                                  592|1007.7|970|
#> 90                                                                                                                              522|1694|802.8|520|
#> 91                                                                                                                      953|6687|957|700|5654|1119|
#> 92                                                                                                 2625|2958|2625|3217.56|3378.56|1251|342|500|201|
#> 93                                                                                                                                342|2744|952|500|
#> 94                                                                                                                1680|1680|3691|550|2396|500|1000|
#> 95                                                                                              9001|2100.91|2100.84|2249|2100|887|1390|20616|1780|
#> 96                                                                                                                             9001|2573|500|558.7|
#> 97                                                                                                                                    749|773|1000|
#> 98                                                                                                                                      1500|13115|
#> 99                                                   3572|455|1054|4216|3821|4215|4217|4213|4218|4246|4214|4113|4091|4216|3526|6910|9533|9433|7113|
#> 100                                                                                                                                      1009|2378|
#>                                                                                                      WT_GLIR
#> 1   0|0|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|0.3|
#> 2                0.5|0.6|0.1|0.1|0.25|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.265|
#> 3                                                               0.2|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|
#> 4                                                     0|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|
#> 5                                                       0.3|0.5|0.3|0.3|0.3|0.1|0.4|0.2|0.2|0.3|0.2|0.1|0.1|
#> 6                                                                   0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 7                                                                                             0.28|0.1|0.33|
#> 8                                                                                                  0.18|0.1|
#> 9                                                                                                  0.18|0.2|
#> 10                                                                                                  0.2|0.5|
#> 11                                                                                                    0.2|0|
#> 12                                                                                              0.2|0.1|0.4|
#> 13                                                                                             0.2|0.27|0.2|
#> 14                                                                                              0|0.074|0.3|
#> 15                                                                                                         0
#> 16                                                                                                         0
#> 17                                                                                               0.649999976
#> 18                                                                                                         0
#> 19                                                                                               0.610000014
#> 20                                                                                                         0
#> 21                                           0.865|0.869|0.84|0.6|0.555|0.18|0.4|0.438|0.436|0.366|0.3|0.41|
#> 22                                                   0.459|0.465|0.44|0.52|0.58|0.37|0.509|0.5|0.35|0.3|0.3|
#> 23                                                                 0.65|0.17|0.31|0.246|0.03|0.461|0.15|0.4|
#> 24                                                                  0.212|0.482|0.6|0.9|0.6|0.53|0.08|0.593|
#> 25                                                                                                  0.6|0.1|
#> 26                                                                                               0.589999974
#> 27                                                                                             0.2|0.5|0.45|
#> 28                                                                                               0.270000011
#> 29                                                                                               0.150000006
#> 30                                                                                                  0.6|0.1|
#> 31                                                                                         475|430|550|0.27|
#> 32                                                                                               0.275000006
#> 33                                                                                               0.282999992
#> 34                                                                                                0.3|0.285|
#> 35                                                                                               0.200000003
#> 36                                                                    0.47|0.5|0.33|0.42|0.98|0.38|0.94|0|0|
#> 37                                                                                               0.200000003
#> 38                                                                                           0.5|0.518|0.75|
#> 39                                                                                                         0
#> 40                                                                                               0.509000003
#> 41                                                                                               0.510999978
#> 42                                                                                                0.81400001
#> 43                                                                                               0.100000001
#> 44                                                                                               0.319999993
#> 45                                             0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.27|
#> 46                                                                                                 0.4|0.18|
#> 47                                                                                                0.35|0.91|
#> 48                                                                                      0.35|0.35|0.35|0.23|
#> 49                                       0.154|0.154|0.106|0.127|0.213|0.271|0.194|0.11|0.125|0.2288|0|0.12|
#> 50                                              0|0|0|0|0|0.63889|0.63889|0.63889|0.63889|0.63889|0.305|0.6|
#> 51                                                0|0|0.35494|0|0|0.35494|0.49691|0.49691|0.20341|0.09|0.22|
#> 52                                                                                     0|0|0|0.145|0.2|0.42|
#> 53                                                                                            0.24|0.41|0.3|
#> 54                                                                                          0.24|0.41|0.575|
#> 55                                                                                               0.140000001
#> 56                                                                                               0.216000006
#> 57                                                                                     0.4|0.5|0.4|0.4|0.43|
#> 58                                                                                                0.1|0.305|
#> 59                                                                                                  0.3|0.4|
#> 60                                                                                              0.15|0.1567|
#> 61                                                    0|0|0|0.35494|0.35494|0.35494|0.35494|0.35494|0.1|0.3|
#> 62                                                                                  0.218|0|0.21|0.21|0.161|
#> 63                                                                                              0.5|0.1|0.3|
#> 64                                                                                                         0
#> 65                                                                                   0.183|0.174|0.17|0.265|
#> 66                                                                                                0.19|0.24|
#> 67                                                                                            0|0.3|0.1|0.6|
#> 68                                                                                             0.35|0|0.458|
#> 69                                                                                              0.2|0.2|0.2|
#> 70                                                                                               0.805000007
#> 71                                                                                               0.200000003
#> 72                                                                                               0.239999995
#> 73                                                                                           0.46|0.38|0.38|
#> 74                                                                                               0.125|0.15|
#> 75                                                                        0.04|0.6|0.56|0.75|0.06|0.48|0.35|
#> 76                                                                                             0.15|0.3|0.2|
#> 77                                                                           0|0|0|0.27|0|0|0|0.23|0.1|0.36|
#> 78                                                                        0.1|0.3|0.3|0|0.1|1|0.1|0.33|0.33|
#> 79                                                                                           0.1|0.015|0.02|
#> 80                                                                                               0.100000001
#> 81                                                                                               0.100000001
#> 82                                                                                               0.280000001
#> 83                                                                   0.096|0.047|0|0.05|0.05|0.96|0.47|0.17|
#> 84                                                                                         0.162|0.38|0.185|
#> 85                                                         0.165|0.3|0.3|0.12|0.34|0.34|0.34|0.39|0.55|0.55|
#> 86                                                                  0.47|0.7|0.3|0.98|0.67|0.375|0.56|0.325|
#> 87                                                                          0.33902|0.14|0.18|0.26|0.41|0.6|
#> 88                                                                                     0.033|0|0.2161|0.339|
#> 89                                                                                        0.3|0.1075|0.1075|
#> 90                                                                                         0.6|0.47|0.3|0.1|
#> 91                                                                             0.24|0.47|0.47|0.1|0.205|0.2|
#> 92                                                              0.096|0.047|0|0.05|0.05|0.43|0.24|0.29|0.11|
#> 93                                                                                          0.98|0.5|0|0.29|
#> 94                                                                          0|0.635|0.158|0.343|1|0.5|0.535|
#> 95                                                       0.1|0.29664|0.295|0.29664|0.15|0.14|0.15|0.33|0.33|
#> 96                                                                                        0.1|0.128|0.5|0.3|
#> 97                                                                                            0.48|0.48|0.5|
#> 98                                                                                                0.1|0.118|
#> 99                             0.35|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.5|0.1|0.1|0.1|0.1|0.1|
#> 100                                                                                                 0.2|0.2|
#>                                                                                                                                                                                                                     WT_DEPTH
#> 1   1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|1807.53|
#> 2                                                                 1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|
#> 3                                                                                                                                                                    1227|1227|1227|1227|1227|1227|1227|1227|1227|1227|1227|
#> 4                                                                                                                         1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|1569.6|
#> 5                                                                                                                               2142.8|2142.8|2142.8|2142.8|2142.8|2142.8|1911.98|2142.8|2142.8|2142.8|2142.8|2142.8|2142.8|
#> 6                                                                                                                                                                                   0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 7                                                                                                                                                                                                   1675.82|1675.82|1675.82|
#> 8                                                                                                                                                                                                             1596.5|1596.5|
#> 9                                                                                                                                                                                                                 1318|1318|
#> 10                                                                                                                                                                                                                1372|1372|
#> 11                                                                                                                                                                                                                1668.12|0|
#> 12                                                                                                                                                                                                     2288.4|2288.4|2288.4|
#> 13                                                                                                                                                                                                  1800.82|1800.82|1800.82|
#> 14                                                                                                                                                                                                          0|1249.1|1249.1|
#> 15                                                                                                                                                                                                                         0
#> 16                                                                                                                                                                                                            1817.300050781
#> 17                                                                                                                                                                                                            1581.999957422
#> 18                                                                                                                                                                                                                         0
#> 19                                                                                                                                                                                                            1613.800062891
#> 20                                                                                                                                                                                                                         0
#> 21                                                                                                                                                              1491|1491|1491|1491|1491|1491|1491|1491|1491|1491|1491|1491|
#> 22                                                                                                                                                        603.5|603.5|603.5|603.5|603.5|603.5|603.5|603.5|603.5|603.5|603.5|
#> 23                                                                                                                                                                  1832.8|1832.8|1832.8|1832.8|1832.8|1832.8|1832.8|1832.8|
#> 24                                                                                                                                                                  1367.7|1367.7|1367.7|1367.7|1367.7|1367.7|1367.7|1367.7|
#> 25                                                                                                                                                                                                            1333.5|1333.5|
#> 26                                                                                                                                                                                                            1323.899990625
#> 27                                                                                                                                                                                                     1876.3|1876.3|1876.3|
#> 28                                                                                                                                                                                                            1189.799971289
#> 29                                                                                                                                                                                                            1456.400033203
#> 30                                                                                                                                                                                                                1362|1362|
#> 31                                                                                                                                                                                              2138.8|2138.8|2138.8|2138.8|
#> 32                                                                                                                                                                                                             1108.00001543
#> 33                                                                                                                                                                                                            1098.950000391
#> 34                                                                                                                                                                                                                1507|1507|
#> 35                                                                                                                                                                                                            2350.700050781
#> 36                                                                                                                                                  1258.22|1258.22|1258.22|1258.22|1258.22|1258.22|1258.22|1258.22|1258.22|
#> 37                                                                                                                                                                                                            1609.000058203
#> 38                                                                                                                                                                                                     1174.7|1174.7|1174.7|
#> 39                                                                                                                                                                                                                         0
#> 40                                                                                                                                                                                                            1597.000046484
#> 41                                                                                                                                                                                                             886.000021875
#> 42                                                                                                                                                                                                            1604.000028516
#> 43                                                                                                                                                                                                               1599.999975
#> 44                                                                                                                                                                                                            1840.000060547
#> 45                                                                                                                 1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|
#> 46                                                                                                                                                                                                             683.6|2030.5|
#> 47                                                                                                                                                                                                              1772|1772.6|
#> 48                                                                                                                                                                                                    1635|1635|1635|1634.6|
#> 49                                                                                                                                     1772.6|1772.6|1772.6|1772.6|1772.6|1772.6|1772.6|1772.6|1772.6|2319.5|2319.5|2406.11|
#> 50                                                                                                                                                                             0|0|0|0|0|1605|1605|1605|1605|1605|1605|1605|
#> 51                                                                                                                                                   0|1324.7|1324.7|1324.7|1324.7|1324.7|1324.7|1324.7|1324.7|978.6|1324.7|
#> 52                                                                                                                                                                                               0|0|0|1315.1|1315.1|1315.1|
#> 53                                                                                                                                                                                                         1438|1438|1438.1|
#> 54                                                                                                                                                                                                           1438|1438|1438|
#> 55                                                                                                                                                                                                            2020.900051172
#> 56                                                                                                                                                                                                            2319.500020313
#> 57                                                                                                                                                                                       1864.7|1864.7|1864.7|1864.7|1864.7|
#> 58                                                                                                                                                                                                              1356|1197.8|
#> 59                                                                                                                                                                                                                 418|1535|
#> 60                                                                                                                                                                                                                  856|841|
#> 61                                                                                                                                                                                 0|0|0|1184|1184|1184|1184|1184|1184|1184|
#> 62                                                                                                                                                                                               1366.1|1366|1366|1366|1203|
#> 63                                                                                                                                                                                                         1126|1126|1126.4|
#> 64                                                                                                                                                                                                                      1420
#> 65                                                                                                                                                                                                      2159|2159|2159|2159|
#> 66                                                                                                                                                                                                            2252.5|2252.5|
#> 67                                                                                                                                                                                              1168.5|1168.5|1168.5|1168.5|
#> 68                                                                                                                                                                                                          1346.7|0|1490.9|
#> 69                                                                                                                                                                                                           1322|1322|1322|
#> 70                                                                                                                                                                                                            1800.900024414
#> 71                                                                                                                                                                                                            1500.600051563
#> 72                                                                                                                                                                                                            1748.000020313
#> 73                                                                                                                                                                                                  6955.05|6955.05|6955.05|
#> 74                                                                                                                                                                                                          5773.62|5773.62|
#> 75                                                                                                                                                                  4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|
#> 76                                                                                                                                                                                                  6328.74|6328.74|6328.74|
#> 77                                                                                                                                                            0|0|0|5114.83|5114.83|5115.81|5115.81|5115.81|4547.24|4547.24|
#> 78                                                                                                                                                  4548.88|8851.71|8851.71|8851.71|5120.08|8851.71|2040.68|2040.68|2040.68|
#> 79                                                                                                                                                                                                    4548.88|3747.7|3747.7|
#> 80                                                                                                                                                                                                            4548.884277344
#> 81                                                                                                                                                                                                            4548.884277344
#> 82                                                                                                                                                                                                            4285.433105469
#> 83                                                                                                                                                          4199.48|4199.48|4199.48|4199.48|4199.48|4199.48|4199.48|4199.48|
#> 84                                                                                                                                                                                                  2637.47|2637.47|2637.47|
#> 85                                                                                                                                          4887.11|4887.11|4887.11|4887.11|4887.11|4887.11|4887.11|4887.11|4887.11|4887.11|
#> 86                                                                                                                                                          7542.65|7542.65|7542.65|7542.65|7542.65|7542.65|7542.65|7542.65|
#> 87                                                                                                                                                                          4063.65|4063.65|4063.65|4063.65|4063.65|4063.65|
#> 88                                                                                                                                                                                          4061.35|4061.35|4061.35|4061.35|
#> 89                                                                                                                                                                                                  5459.97|5459.97|5459.97|
#> 90                                                                                                                                                                                          5167.32|5167.32|5167.32|5167.32|
#> 91                                                                                                                                                                          3415.35|3415.35|3415.35|3415.35|3415.35|3415.35|
#> 92                                                                                                                                                  4199.48|4199.48|4199.48|4199.48|4199.48|3986.22|3986.22|3986.22|3986.22|
#> 93                                                                                                                                                                                          5019.69|5019.69|5019.69|5019.69|
#> 94                                                                                                                                                                     6420.6|6420.6|6420.6|6826.77|6826.77|6826.77|6826.77|
#> 95                                                                                                                                                      4548.88|7939.3|7939.3|7939.3|6866.8|6867.78|6867.78|6867.78|6867.78|
#> 96                                                                                                                                                                                          4548.88|4547.24|4532.48|4532.48|
#> 97                                                                                                                                                                                                  5774.61|5774.61|5774.61|
#> 98                                                                                                                                                                                                          3937.01|2795.28|
#> 99                                                                                     1378.4|1348.1|1348.1|1348.1|1348.1|1348.1|1348.1|1348.1|1348.1|1348.1|1348.1|1348.1|1348.1|1348.1|1348.1|1348.1|1348.1|1348.1|1348.1|
#> 100                                                                                                                                                                                                               1404|1404|
#>                                                  WT_Enable
#> 1   0|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|
#> 2             1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 3                                   1|1|1|1|1|1|1|1|1|0|1|
#> 4                             1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 5                               1|1|1|1|1|1|0|1|1|1|1|1|1|
#> 6                 1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|1|1|1|
#> 7                                                   1|1|0|
#> 8                                                     0|1|
#> 9                                                     0|1|
#> 10                                                    1|0|
#> 11                                                    0|1|
#> 12                                                  0|1|1|
#> 13                                                  1|0|1|
#> 14                                                  1|1|0|
#> 15                                                       0
#> 16                                                       0
#> 17                                                       0
#> 18                                                       0
#> 19                                                       0
#> 20                                                       0
#> 21                                1|1|1|1|1|1|1|1|1|1|0|1|
#> 22                                  1|1|1|1|1|1|1|1|1|1|0|
#> 23                                        1|1|1|1|1|1|1|0|
#> 24                                        1|1|1|1|1|1|1|0|
#> 25                                                    0|1|
#> 26                                                       0
#> 27                                                  1|1|0|
#> 28                                                       0
#> 29                                                       0
#> 30                                                    1|0|
#> 31                                                1|1|1|0|
#> 32                                                       0
#> 33                                                       0
#> 34                                                    1|0|
#> 35                                                       0
#> 36                                      0|1|1|1|1|1|1|1|1|
#> 37                                                       0
#> 38                                                  0|1|1|
#> 39                                                       0
#> 40                                                       0
#> 41                                                       0
#> 42                                                       0
#> 43                                                       0
#> 44                                                       0
#> 45                          1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 46                                                    1|0|
#> 47                                                    1|0|
#> 48                                                1|1|1|0|
#> 49                                1|1|1|1|1|1|1|1|1|1|1|0|
#> 50                                1|1|1|1|1|1|1|1|1|1|1|0|
#> 51                                  1|1|1|1|1|1|1|1|1|1|0|
#> 52                                            1|1|1|1|1|0|
#> 53                                                  1|1|0|
#> 54                                                  1|1|0|
#> 55                                                       0
#> 56                                                       0
#> 57                                              1|1|1|1|0|
#> 58                                                    1|0|
#> 59                                                    1|0|
#> 60                                                    1|0|
#> 61                                    1|1|1|1|1|1|1|1|1|0|
#> 62                                              1|1|1|1|0|
#> 63                                                  1|1|0|
#> 64                                                       0
#> 65                                                1|1|1|0|
#> 66                                                    1|0|
#> 67                                                1|1|1|0|
#> 68                                                  1|1|0|
#> 69                                                  1|1|0|
#> 70                                                       0
#> 71                                                       0
#> 72                                                       0
#> 73                                                  1|1|0|
#> 74                                                    1|0|
#> 75                                          1|1|1|1|1|1|0|
#> 76                                                  1|1|0|
#> 77                                    1|1|1|1|1|1|1|1|1|0|
#> 78                                      1|1|1|1|1|1|1|1|0|
#> 79                                                  1|1|0|
#> 80                                                       0
#> 81                                                       0
#> 82                                                       0
#> 83                                        1|1|1|1|1|1|1|0|
#> 84                                                  1|1|0|
#> 85                                    1|1|1|1|1|1|1|1|1|0|
#> 86                                        1|1|1|1|1|1|1|0|
#> 87                                            1|1|1|1|1|0|
#> 88                                                1|1|1|0|
#> 89                                                  1|1|0|
#> 90                                                1|1|1|0|
#> 91                                            1|1|1|1|1|0|
#> 92                                      1|1|1|1|1|1|1|0|1|
#> 93                                                1|1|1|0|
#> 94                                          1|1|1|1|1|1|0|
#> 95                                      1|1|1|1|1|1|1|1|0|
#> 96                                                1|1|1|0|
#> 97                                                  1|0|1|
#> 98                                                    1|0|
#> 99                  0|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|
#> 100                                                   0|1|
#>                                                                         WT_GDEPTH
#> 1                          0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 2                                    0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 3                                                          0|0|0|0|0|0|0|0|0|0|0|
#> 4                                                    0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 5                                                      0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 6                                        0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 7                                                                          0|0|0|
#> 8                                                                  1684.5|1684.5|
#> 9                                                                            0|0|
#> 10                                                                           0|0|
#> 11                                                                     0|1781.52|
#> 12                                                                         0|0|0|
#> 13                                                                         0|0|0|
#> 14                                                          1442.2|1442.2|1442.2|
#> 15                                                                              0
#> 16                                                                              0
#> 17                                                                              0
#> 18                                                                              0
#> 19                                                                              0
#> 20                                                                              0
#> 21                                                       0|0|0|0|0|0|0|0|0|0|0|0|
#> 22                                                         0|0|0|0|0|0|0|0|0|0|0|
#> 23                                                               0|0|0|0|0|0|0|0|
#> 24                                                               0|0|0|0|0|0|0|0|
#> 25                                                                           0|0|
#> 26                                                                              0
#> 27                                                                         0|0|0|
#> 28                                                                              0
#> 29                                                                              0
#> 30                                                                           0|0|
#> 31                                                                       0|0|0|0|
#> 32                                                                              0
#> 33                                                                              0
#> 34                                                                           0|0|
#> 35                                                                              0
#> 36                                                             0|0|0|0|0|0|0|0|0|
#> 37                                                                              0
#> 38                                                                      0|0|1731|
#> 39                                                                              0
#> 40                                                                              0
#> 41                                                                              0
#> 42                                                                              0
#> 43                                                                              0
#> 44                                                                              0
#> 45                                                 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 46                                                                        2258|0|
#> 47                                                                           0|0|
#> 48                                                                       0|0|0|0|
#> 49  1772.6|1772.6|1772.6|1772.6|1772.6|1772.6|1772.6|1772.6|1772.6|2499.3|2438|0|
#> 50                                                    1|1|1|1|1|1|1|1|1|1|1634|0|
#> 51     0.3048|0.3048|0.3048|0.3048|0.3048|0.3048|0.3048|0.3048|429.555|1504.47|0|
#> 52                                                          1518|1518|1518|0|0|0|
#> 53                                                                         0|0|0|
#> 54                                                                         0|0|0|
#> 55                                                                              0
#> 56                                                                 2442.300041016
#> 57                                                      2312.5|0|2312.5|2312.5|0|
#> 58                                                                     1409|1409|
#> 59                                                                        1915|0|
#> 60                                                                     1374|1371|
#> 61                                                        1|1|1|1|1|1|1|1|1260|0|
#> 62                                                                     0|0|0|0|0|
#> 63                                                                    0|0|1278.8|
#> 64                                                                              0
#> 65                                                                       0|0|0|0|
#> 66                                                                 2517.8|2517.9|
#> 67                                                                    1293|0|0|0|
#> 68                                                                    0|1622.9|0|
#> 69                                                                         0|0|0|
#> 70                                                                              0
#> 71                                                                              0
#> 72                                                                              0
#> 73                                                             7273.62|0|7273.62|
#> 74                                                                 5856.3|5856.3|
#> 75                                               0|0|0|5141.08|5141.08|0|5141.08|
#> 76                                                                   6542.98|0|0|
#> 77                       4625.92|4625.92|4625.92|0|0|0|0|5515.09|5561.02|5561.02|
#> 78                                     0|0|0|9186.35|9186.35|0|9186.35|0|9186.35|
#> 79                                                                   0|0|4734.58|
#> 80                                                                              0
#> 81                                                                              0
#> 82                                                                 7372.047363281
#> 83                                                               0|0|0|0|0|0|0|0|
#> 84                                                       4558.07|4558.07|4558.07|
#> 85                                         9484.91|0|0|0|0|0|9500.98|9500.98|0|0|
#> 86                                                   0|0|0|0|0|8874.67|0|8874.67|
#> 87                                                 4454.66|0|4419.29|0|0|4419.29|
#> 88                                                                       0|0|0|0|
#> 89                                                             6279.53|0|6279.53|
#> 90                                                     6056.43|6056.43|0|6056.43|
#> 91                                                 0|0|5521.65|5521.65|0|5521.65|
#> 92                                                       0|0|0|0|0|0|0|4652.23|0|
#> 93                                                                 0|0|0|6089.24|
#> 94                                                  0|0|0|7029.2|0|6952.1|6952.1|
#> 95                   0|13517.7|13517.7|13517.7|13556.4|13556.4|13556.4|0|13556.4|
#> 96                                                     0|4665.35|4666.34|4666.34|
#> 97                                                                   0|6008.86|0|
#> 98                                                                     0|4429.13|
#> 99                                         0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 100                                                                          0|0|
#>                                                                                                                                               WT_GPRES
#> 1   246.5|232.1|246.6|217.6|246.6|217.6|217.6|203|203|203|232.1|232.1|232.1|232.1|261.1|217.6|246.6|232.1|232|232.1|232.1|232|217.5|203|203|232|246.5|
#> 2                            246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 3                                                                                                 435|304.5|348|348|334|334|304.5|334|304.5|290|435.1|
#> 4                                                                 362.6|464.1|507.6|507.6|319.1|304.6|290.1|304.6|304.6|304.6|290.1|319.1|391.6|362.6|
#> 5                                                                       261.1|217.6|246.6|232.1|232.1|217.6|261.1|217.6|261.1|217.6|246.6|246.6|217.6|
#> 6                                   304.6|362.6|304.6|348.1|319.1|290.1|246.6|261.1|290.1|333.6|362.6|304.6|261.1|275.6|275.5|319|333.5|188.5|319|290|
#> 7                                                                                                                                         261|290|290|
#> 8                                                                                                                                         1038.14|988|
#> 9                                                                                                                                         290.1|101.5|
#> 10                                                                                                                                        246.6|377.1|
#> 11                                                                                                                                            720|990|
#> 12                                                                                                                                  246.6|246.6|217.6|
#> 13                                                                                                                                        232|232|232|
#> 14                                                                                                                               1328.5|1328.5|1328.5|
#> 15                                                                                                                                       261.000000854
#> 16                                                                                                                                               362.5
#> 17                                                                                                                                                 290
#> 18                                                                                                                                       348.100006104
#> 19                                                                                                                                               304.5
#> 20                                                                                                                                                 232
#> 21                                                    217.696|232.696|217.696|203.696|232.696|232.696|246.696|232.696|203.696|188.696|145.696|130.696|
#> 22                                                                                                     101.5|101.53|101.5|261|87|80|87|101.5|87|87|87|
#> 23                                                                                    188.696|203.696|203.696|246.696|232.696|174.696|203.696|159.696|
#> 24                                                                                                                  160|247|247|247|243|261|247|217.5|
#> 25                                                                                                                                            218|218|
#> 26                                                                                                                                       217.500000854
#> 27                                                                                                                                  101.5|188.5|246.5|
#> 28                                                                                                                                               130.5
#> 29                                                                                                                                       130.199996948
#> 30                                                                                                                                          101.5|102|
#> 31                                                                                                                      261.696|203.696|275.696|130.5|
#> 32                                                                                                                                                 232
#> 33                                                                                                                                                 232
#> 34                                                                                                                                             102|87|
#> 35                                                                                                                                                 160
#> 36                                                                                                  217.557|203.053|261|290|261|275.5|261|217.5|246.5|
#> 37                                                                                                                                                  87
#> 38                                                                                                                             203.304|203.304|1082.3|
#> 39                                                                                                                                                 290
#> 40                                                                                                                                                 160
#> 41                                                                                                                                                 116
#> 42                                                                                                                                               188.5
#> 43                                                                                                                                                  87
#> 44                                                                                                                                               159.5
#> 45                                                                    217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 46                                                                                                                                         1441|188.6|
#> 47                                                                                                                                            203|200|
#> 48                                                                                                                                  217|246|304|214.3|
#> 49                                                                                            980|980|980|980|980|980|980|980|980|823.991|1004.74|276|
#> 50                                                      0.14504|0.14504|0.14504|0.14504|0.14504|0.14504|0.14504|0.14504|0.14504|0.14504|660.26|217.56|
#> 51                                                                           14.841|14.841|14.841|14.841|14.841|14.841|14.841|14.841|767.606|1236|218|
#> 52                                                                                                              982.195|710.317|705.396|188.5|218|218|
#> 53                                                                                                                                      195|246.5|290|
#> 54                                                                                                                                    195|246.5|214.3|
#> 55                                                                                                                                                 261
#> 56                                                                                                                                       936.089981934
#> 57                                                                                                                            633|261|610.4|655|217.9|
#> 58                                                                                                                                         483|717.41|
#> 59                                                                                                                                           1040|275|
#> 60                                                                                                                                          1130|1140|
#> 61                                                                        0.14504|0.14504|0.14504|0.14504|0.14504|0.14504|0.14504|0.14504|1392.86|290|
#> 62                                                                                                                              275|290|232|246.5|261|
#> 63                                                                                                                                    203|261|1261.65|
#> 64                                                                                                                                                 261
#> 65                                                                                                                                  203|203|217.6|261|
#> 66                                                                                                                                     1211.51|1047.2|
#> 67                                                                                                                               521.84|188.6|232|214|
#> 68                                                                                                                                  188.6|1452.22|203|
#> 69                                                                                                                                  217.6|217.6|217.5|
#> 70                                                                                                                                       203.100006958
#> 71                                                                                                                                       217.600006958
#> 72                                                                                                                                               188.5
#> 73                                                                                                                            917.006|245.696|743.749|
#> 74                                                                                                                                    574.078|656.284|
#> 75                                                                                            173.696|214.696|188.696|736.188|738.696|217.696|584.258|
#> 76                                                                                                                                531.484|414.7|417.5|
#> 77                                                                                     1341.03|826.728|948.84|232|203|232|203|1014.36|1443.22|912.957|
#> 78                                                                                          159.304|261|232|1009.48|1159.51|208|1226.67|265.2|668.011|
#> 79                                                                                                                                174|119.696|860.421|
#> 80                                                                                                                                       174.000000854
#> 81                                                                                                                                       174.000000854
#> 82                                                                                                                                       589.099991699
#> 83                                                                                         174.24|156.84|159.74|174.24|174.24|213.696|171.696|246.696|
#> 84                                                                                                                             1019.74|395.954|658.66|
#> 85                                                                                803|261|275|246.696|228.696|217.696|984.244|746.289|304.696|304.696|
#> 86                                                                                    275.696|231.696|377.696|203.696|231.696|851.995|231.696|971.935|
#> 87                                                                                                             795.52|193|1241.83|174|246.696|1086.17|
#> 88                                                                                                                                    159|130|246|203|
#> 89                                                                                                                            673.926|217.596|977.482|
#> 90                                                                                                                        698.993|890|232.196|1364.11|
#> 91                                                                                                    214.696|191.696|711.191|570.416|246.696|692.188|
#> 92                                                                                  174.24|156.84|159.74|174.24|174.24|275.696|290.196|1381.1|246.696|
#> 93                                                                                                                    174.696|275.696|173.696|1053.14|
#> 94                                                                                            289.696|318.696|449.696|932.635|286.096|820.055|555.593|
#> 95                                                                                     174|1096.92|1007.6|1285.93|867|1061.02|1246.47|259.196|1202.02|
#> 96                                                                                                                               174|956|872.757|1215|
#> 97                                                                                                                             333.696|949.975|14.696|
#> 98                                                                                                                                       144.696|1180|
#> 99                                        319|246.6|261.1|261.1|261.1|261.1|246.6|290.1|290.1|290.1|261.1|290.1|290.1|348.1|319.1|275.6|275.5|261|319|
#> 100                                                                                                                                           290|522|
#>                                                                                                         WT_RESPRES
#> 1     930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|930|
#> 2   1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|
#> 3                                                          1573|1573|1573|1573|1573|1573|1573|1573|1573|1573|1573|
#> 4                                           1286|1025|1025|1025|1025|1025|1025|1025|1025|1025|1025|1025|1025|1025|
#> 5                                                 1468|900|1468|1468|1468|1468|1468|1468|1468|1468|1468|1468|1468|
#> 6             1286|1286|1286|1286|1286|1286|1286|1286|1286|1286|1286|1286|1286|1286|1286|1286|1275|1286|1286|1286|
#> 7                                                                                            1459.5|1459.5|1459.5|
#> 8                                                                                                     1107|1167.6|
#> 9                                                                                                       1526|1526|
#> 10                                                                                                  1308.5|1311.7|
#> 11                                                                                                      1236|1742|
#> 12                                                                                                 1034|1034|1034|
#> 13                                                                                                 1406|1406|1406|
#> 14                                                                                                 1600|1600|1600|
#> 15                                                                                                  1205.999955078
#> 16                                                                                                  1028.787597656
#> 17                                                                                                            1526
#> 18                                                                                                            1407
#> 19                                                                                                            1312
#> 20                                                                                                            1126
#> 21                               1214.7|1214.7|1214.7|1214.7|1214.7|1214.7|1214.7|1214.7|1214.7|1214.7|830|1214.7|
#> 22                                                                    600|600|600|600|600|600|600|600|600|600|800|
#> 23                                                                        1300|1300|1300|1300|1300|1300|1300|1300|
#> 24                                                                    1100|1100|1100|1100|1285.3|1100|1100|1285.3|
#> 25                                                                                                      1100|1100|
#> 26                                                                                                  1599.999955078
#> 27                                                                                                 1321|1321|1300|
#> 28                                                                                                            1313
#> 29                                                                                                             850
#> 30                                                                                                        658|658|
#> 31                                                                                            1300|1300|1300|1300|
#> 32                                                                                                    1560.7109375
#> 33                                                                                                    1560.7109375
#> 34                                                                                                1088.03|1088.03|
#> 35                                                                                                            1400
#> 36                                                                   1500|1500|1500|1500|1500|1500|1500|1500|1500|
#> 37                                                                                                            1080
#> 38                                                                                                 1441|1441|1441|
#> 39                                                                                                            2727
#> 40                                                                                                            1225
#> 41                                                                                                            1250
#> 42                                                                                                            1161
#> 43                                                                                                            1036
#> 44                                                                                                            1611
#> 45                                     1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|
#> 46                                                                                                       1700|951|
#> 47                                                                                                      1200|1374|
#> 48                                                                                            1400|1400|1400|1272|
#> 49                                                     1200|1200|1200|1200|1200|1200|1200|1200|1200|1004|910|1539|
#> 50                        1203.81|1203.81|1203.81|1203.81|1015.26|1015.26|1015.26|1087.78|1087.78|1160.3|876|1236|
#> 51                                  1414.7|1314.7|1214.7|1114.7|764.696|764.686|764.686|764.541|999.697|1663|1663|
#> 52                                                                         1198.12|1198.12|1198.12|1243|1243|1243|
#> 53                                                                                                 1367|1300|1750|
#> 54                                                                                                 1367|1300|1367|
#> 55                                                                                                            1247
#> 56                                                                                                  1058.259964844
#> 57                                                                                       1285|1285|1200|1200|1224|
#> 58                                                                                                       1120|810|
#> 59                                                                                                      1400|1380|
#> 60                                                                                                      1500|1550|
#> 61                                       1102.29|1116.79|1145.8|1392.36|1392.36|1392.36|1247.32|1298.09|1645|1663|
#> 62                                                                                       1500|1550|1650|1550|1615|
#> 63                                                                                              1445.41|1500|1550|
#> 64                                                                                                   930.314331055
#> 65                                                                                            1400|1400|1400|1400|
#> 66                                                                                                   1373.09|1373|
#> 67                                                                                            1407|1407|1407|1407|
#> 68                                                                                                 1566|1566|1566|
#> 69                                                                                                 1400|1400|1400|
#> 70                                                                                                  1338.999955078
#> 71                                                                                                  1535.999955078
#> 72                                                                                                  1363.790039063
#> 73                                                                                           1574.7|1574.7|1574.7|
#> 74                                                                                                      1600|1600|
#> 75                                                               1714.7|1698.7|1695.7|1695.7|1695.7|1695.7|1695.7|
#> 76                                                                                          949.696|1114.7|1114.7|
#> 77                                                        2929.3|2929.3|2929.3|1550|1550|1550|1550|1560|1560|1560|
#> 78                                                            1499.3|1485.3|1276.52|1485|1485|1485|1485|1485|1485|
#> 79                                                                                             1514|1513.7|1513.7|
#> 80                                                                                                  1513.999955078
#> 81                                                                                                  1513.999955078
#> 82                                                                                                        1695.696
#> 83                                                               1500|1500|1500|1500|1500|1480.74|1480.74|1480.74|
#> 84                                                                                           1425.3|1425.3|1425.3|
#> 85                                                1514|1400|1400|1399.7|1591.7|1591.7|1591.7|1591.7|1591.7|1591.7|
#> 86                                                        1514.7|1514.7|1574.7|1574.7|1574.7|1574.7|1574.7|1574.7|
#> 87                                                                               969.233|1480|1480|1480|1480|1480|
#> 88                                                                                            1400|1400|1400|1400|
#> 89                                                                                           1564.7|1564.7|1564.7|
#> 90                                                                                            1686|1686|1686|1686|
#> 91                                                                      1591.7|1591.7|1591.7|1591.7|1591.7|1591.7|
#> 92                                                           1500|1500|1500|1500|1500|1664.7|1664.7|1664.7|1664.7|
#> 93                                                                                    1638.7|1638.7|1622.7|1622.7|
#> 94                                                            1225.77|1225.77|1225.77|1414.7|1414.7|1414.7|1414.7|
#> 95                                               1513.99|1465.67|1465.67|1465.67|1465|1664.7|1664.7|1664.7|1664.7|
#> 96                                                                                            1514|1514|1580|1580|
#> 97                                                                                           1494.7|1494.7|1494.7|
#> 98                                                                                                  1214.7|1620.7|
#> 99                 1388|1388|1388|1388|1388|1388|1388|1388|1388|1388|1388|1388|1388|1388|1388|1388|1388|1388|1388|
#> 100                                                                                                     1600|1600|
#>                                            ProsperFilename
#> 1       \\\\network\\piscis\\well_models\\PISC-M005-TS.Out
#> 2       \\\\network\\piscis\\well_models\\PISC-M007-TS.Out
#> 3       \\\\network\\piscis\\well_models\\PISC-M004-LL.Out
#> 4       \\\\network\\piscis\\well_models\\PISC-M008-TS.Out
#> 5       \\\\network\\piscis\\well_models\\PISC-M010-SS.Out
#> 6       \\\\network\\piscis\\well_models\\PISC-M006-TS.Out
#> 7       \\\\network\\piscis\\well_models\\PISC-M016-LS.Out
#> 8       \\\\network\\piscis\\well_models\\PISC-M018-LS.Out
#> 9       \\\\network\\piscis\\well_models\\PISC-M021-LS.Out
#> 10   \\\\network\\piscis\\well_models\\PISC-M017S01-LS.Out
#> 11      \\\\network\\piscis\\well_models\\PISC-M030-SS.Out
#> 12      \\\\network\\piscis\\well_models\\PISC-M027-SS.Out
#> 13      \\\\network\\piscis\\well_models\\PISC-M016-SS.Out
#> 14      \\\\network\\piscis\\well_models\\PISC-M020-LS.Out
#> 15   \\\\network\\piscis\\well_models\\PISC-M028S01-TS.Out
#> 16      \\\\network\\piscis\\well_models\\PISC-M015-LS.Out
#> 17      \\\\network\\piscis\\well_models\\PISC-M018-SS.Out
#> 18      \\\\network\\piscis\\well_models\\PISC-M015-SS.Out
#> 19      \\\\network\\piscis\\well_models\\PISC-M002-LS.Out
#> 20      \\\\network\\piscis\\well_models\\PISC-M012-ST.Out
#> 21      \\\\network\\piscis\\well_models\\PISC-Q007-LS.Out
#> 22      \\\\network\\piscis\\well_models\\PISC-Q001-SS.Out
#> 23      \\\\network\\piscis\\well_models\\PISC-Q005-SS.Out
#> 24      \\\\network\\piscis\\well_models\\PISC-Q011-SS.Out
#> 25       \\\\network\\piscis\\well_models\\PISC-Q02-SS.Out
#> 26      \\\\network\\piscis\\well_models\\PISC-Q002-LS.Out
#> 27      \\\\network\\piscis\\well_models\\PISC-Q003-LS.Out
#> 28      \\\\network\\piscis\\well_models\\PISC-Q004-SS.Out
#> 29      \\\\network\\piscis\\well_models\\PISC-Q009-SS.Out
#> 30      \\\\network\\piscis\\well_models\\PISC-Q019-LS.Out
#> 31      \\\\network\\piscis\\well_models\\PISC-Q032-SS.Out
#> 32      \\\\network\\piscis\\well_models\\PISC-Q028-LS.Out
#> 33      \\\\network\\piscis\\well_models\\PISC-Q028-SS.Out
#> 34      \\\\network\\piscis\\well_models\\PISC-Q029-LS.Out
#> 35      \\\\network\\piscis\\well_models\\PISC-Q032-LS.Out
#> 36      \\\\network\\piscis\\well_models\\PISC-Q024-ST.Out
#> 37      \\\\network\\piscis\\well_models\\PISC-Q018-LS.Out
#> 38      \\\\network\\piscis\\well_models\\PISC-Q017-LS.Out
#> 39      \\\\network\\piscis\\well_models\\PISC-Q013-SS.Out
#> 40      \\\\network\\piscis\\well_models\\PISC-Q014-LS.Out
#> 41      \\\\network\\piscis\\well_models\\PISC-Q017-SS.Out
#> 42      \\\\network\\piscis\\well_models\\PISC-Q014-SS.Out
#> 43      \\\\network\\piscis\\well_models\\PISC-Q018-SS.Out
#> 44      \\\\network\\piscis\\well_models\\PISC-Q012-TS.Out
#> 45      \\\\network\\piscis\\well_models\\PISC-R009-SS.Out
#> 46      \\\\network\\piscis\\well_models\\PISC-R015-LS.Out
#> 47      \\\\network\\piscis\\well_models\\PISC-R019-SS.Out
#> 48      \\\\network\\piscis\\well_models\\PISC-R019-LS.Out
#> 49      \\\\network\\piscis\\well_models\\PISC-R020-LS.Out
#> 50      \\\\network\\piscis\\well_models\\PISC-R013-ST.Out
#> 51      \\\\network\\piscis\\well_models\\PISC-R012-LS.Out
#> 52      \\\\network\\piscis\\well_models\\PISC-R012-SS.Out
#> 53      \\\\network\\piscis\\well_models\\PISC-R018-SS.Out
#> 54      \\\\network\\piscis\\well_models\\PISC-R018-LS.Out
#> 55      \\\\network\\piscis\\well_models\\PISC-R015-SS.Out
#> 56      \\\\network\\piscis\\well_models\\PISC-R020-SS.Out
#> 57      \\\\network\\piscis\\well_models\\PISC-R004-LS.Out
#> 58      \\\\network\\piscis\\well_models\\PISC-R001-SS.Out
#> 59      \\\\network\\piscis\\well_models\\PISC-R003-TS.Out
#> 60      \\\\network\\piscis\\well_models\\PISC-R006-SS.Out
#> 61      \\\\network\\piscis\\well_models\\PISC-R007-LS.Out
#> 62      \\\\network\\piscis\\well_models\\PISC-R001-LS.Out
#> 63      \\\\network\\piscis\\well_models\\PISC-R007-SS.Out
#> 64      \\\\network\\piscis\\well_models\\PISC-R002-SS.Out
#> 65      \\\\network\\piscis\\well_models\\PISC-R029-TS.Out
#> 66      \\\\network\\piscis\\well_models\\PISC-R027-LS.Out
#> 67   \\\\network\\piscis\\well_models\\PISC-R025W01-SS.Out
#> 68      \\\\network\\piscis\\well_models\\PISC-R023-SS.Out
#> 69  \\\\network\\piscis\\well_models\\PISC-R022ST02-TS.Out
#> 70      \\\\network\\piscis\\well_models\\PISC-R021-SS.Out
#> 71      \\\\network\\piscis\\well_models\\PISC-R023-LS.Out
#> 72      \\\\network\\piscis\\well_models\\PISC-R027-SS.Out
#> 73      \\\\network\\piscis\\well_models\\PISC-S008-LS.Out
#> 74      \\\\network\\piscis\\well_models\\PISC-S004-LS.Out
#> 75         \\\\network\\piscis\\well_models\\PISC-S027.Out
#> 76      \\\\network\\piscis\\well_models\\PISC-S019-SS.Out
#> 77      \\\\network\\piscis\\well_models\\PISC-S007-LS.Out
#> 78      \\\\network\\piscis\\well_models\\PISC-S011-SS.Out
#> 79      \\\\network\\piscis\\well_models\\PISC-S016-LS.Out
#> 80      \\\\network\\piscis\\well_models\\PISC-S002-TS.out
#> 81          \\\\network\\piscis\\well_models\\PISCS002.out
#> 82      \\\\network\\piscis\\well_models\\PISC-S019-LS.Out
#> 83      \\\\network\\piscis\\well_models\\PISC-S030-SS.Out
#> 84      \\\\network\\piscis\\well_models\\PISC-S018-LS.Out
#> 85      \\\\network\\piscis\\well_models\\PISC-S026-SS.Out
#> 86         \\\\network\\piscis\\well_models\\PISC-S029.Out
#> 87      \\\\network\\piscis\\well_models\\PISC-S018-SS.Out
#> 88      \\\\network\\piscis\\well_models\\PISC-S013-SS.Out
#> 89      \\\\network\\piscis\\well_models\\PISC-S015-LS.Out
#> 90         \\\\network\\piscis\\well_models\\PISC-S031.Out
#> 91      \\\\network\\piscis\\well_models\\PISC-S032-SS.Out
#> 92      \\\\network\\piscis\\well_models\\PISC-S030-LS.Out
#> 93      \\\\network\\piscis\\well_models\\PISC-S032-LS.Out
#> 94      \\\\network\\piscis\\well_models\\PISC-S006-SS.Out
#> 95         \\\\network\\piscis\\well_models\\PISC-S021.Out
#> 96      \\\\network\\piscis\\well_models\\PISC-S016-SS.Out
#> 97      \\\\network\\piscis\\well_models\\PISC-S015-SS.Out
#> 98      \\\\network\\piscis\\well_models\\PISC-S013-LS.Out
#> 99      \\\\network\\piscis\\well_models\\PISC-M001-TS.Out
#> 100  \\\\network\\piscis\\well_models\\PISC-M026S01-TS.Out
```

Let's use some R functions to find out more about our data.

``` r
# get the dimensions of the table.
dim(myXl)
#> [1] 100  51
```

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

Our table has 100 rows and 51 columns.

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

``` r
# show the data type structure of the table
str(myXl)
#> 'data.frame':    100 obs. of  51 variables:
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
#> [1] "data.frame"
```

Misstyped data
--------------

``` r
unique(myXl$Wellname)
#>  [1] "PSCO-M005-TS"  "PSCO-M0007-TS" "PSCO-M004-LS"  "PSCO-M008-TS" 
#>  [5] "PSCO-M010-SS"  "PSCO-M006-TS"  "PSCO-m016-LS"  "PSCO-M018-LS" 
#>  [9] "PSCO-M021-LS"  "PSCO-M017-LS"  "PSCO-M030-SS"  "PSCO-M027-SS" 
#> [13] "PSCO-M016-SS"  "PSCO-M020-LS"  "PSCO-M028-TS"  "PSCO-M015-LS" 
#> [17] "PSCO-M018-SS"  "PSCO-M015-SS"  "PSCO-M002-LS"  "PSCO-M012-TS" 
#> [21] "PSCO-Q007-LS"  "PSCO-Q001-S"   "PSCO-Q005-SS"  "PSCO-Q011-SS" 
#> [25] "PSCO-Q002-SS"  "PSCO-Q002-LS"  "PSCO-Q003-LS"  "PSCO-Q004-SS" 
#> [29] "PSCO-Q009-SS"  "PSCO-Q019-L"   "PSCO-Q032-SS"  "PSCO-Q028-LS" 
#> [33] "PSCO-Q028-SS"  "PSCO-Q029-LS"  "PSCO-Q032-LS"  "PSCO-Q024-TS" 
#> [37] "PSCO-Q018-LS"  "PSCO-Q017-LS"  "PSCO-Q013-SS"  "PSCO-Q014-LS" 
#> [41] "PSCO-Q017-SS"  "PSCO-Q014-SS"  "PSCO-Q018-SS"  "PSCO-Q012-TS" 
#> [45] "PiSCO-R009-SS" "PSCO-r015-LS"  "PSCO-R019-SS"  "PSCO-R019-LS" 
#> [49] "PSCO-R020-SS"  "PSCO-R013-TS"  "PSCO-R012-LS"  "PSCO-R012-SS" 
#> [53] "PSCO-R018-SS"  "PSCO-R018-LS"  "PSCO-R015-SS"  "PSCO-R004-LS" 
#> [57] "PSCO-R001-SS"  "PSCO-R003-TS"  "PSCO-R006-SS"  "PSCO-R007-LS" 
#> [61] "PSCO-R001-LS"  "PSCO-R007-SS"  "PSCO-R002-SS"  "PSCO-R029-TS" 
#> [65] "PISCO-R027-LS" "PSCO-R025-SS"  "PSCO-R023-SS"  "PSCO-R022-T"  
#> [69] "PSCO-R021-SS"  "PSCO-R023-LS"  "PSCO-R027-SS"  "PSCO-S008-LS" 
#> [73] "PSCO-S004-LS"  "PSCO-027-TS"   "PSCO-S019-SS"  "PSCO-S007-LS" 
#> [77] "PSCO-S011-SS"  "PSCO-S016-LS"  "PSCO-S002-TS"  "PSCO-S019 -LS"
#> [81] "PSCO-S030-SS"  "PSCO-S018-LS"  "PSCO-S026-SS"  "PSCO-S029-TS" 
#> [85] "PSCO-S018-SS"  "PSCO-S013-SS"  "PSCO-S015-LS"  "PSCO-S031-TS" 
#> [89] "PSCO-S032-SS"  "PSCO-S030-LS"  "PSCO-S032-LS"  "PSCO-S006-SS" 
#> [93] "PSCO-S021-TS"  "PSCO-S016-SS"  "PSCO-S015-SS"  "PSCO-S012-LS" 
#> [97] "PSCO-M001-TS"  "PSCO-M0026-TS"
```

Pattern detection
-----------------

``` r
# using a template to find out which well names do not follow a pattern
myXl[!grepl("PSCO-[M,O,P,,Q,R,S][0-9][0-9][0-9]-[T,L,S]S", myXl$Wellname),]
#>          Wellname       Company  Analyst Field Location Platform Fluid
#> 2   PSCO-M0007-TS Oil Gains Co.     Aida PISCO  M007-TS        M     0
#> 7    PSCO-m016-LS Oil Gains Co. Ibironke  <NA>  M016-LS        M     0
#> 22    PSCO-Q001-S Oil Gains Co.  Americo PISCO  Q001-SS        Q     0
#> 30    PSCO-Q019-L Oil Gains Co.   Norman PISCO  Q019-LS        Q     0
#> 45  PiSCO-R009-SS Oil Gains Co.     Aida PISCO  R009-SS        R     0
#> 46   PSCO-r015-LS Oil Gains Co.    Vivek PISCO  R015-LS        R     0
#> 66  PISCO-R027-LS Oil Gains Co.   Norman PISCO  R027-LS        R     0
#> 69    PSCO-R022-T Oil Gains Co.   Norman PISCO  R022-TS        R     0
#> 75    PSCO-027-TS Oil Gains Co.   Andrew PISCO  S027-TS        S     0
#> 82  PSCO-S019 -LS Oil Gains Co.   Andrew PISCO  S019-LS        S     0
#> 100 PSCO-M0026-TS Oil Gains Co. Ibironke PISCO  M026-TS     <NA>     0
#>     WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 2          0         1          0           0       22 473.000    36.0
#> 7          0         1          0           0        3 419.775    35.0
#> 22         0         1          0           0       11 420.000    36.0
#> 30         0         1          0           0        2 415.875    36.0
#> 45         0         1          0           0       15 420.000    36.0
#> 46         0         1          0           0        2 416.000    36.0
#> 66         0         1          0           0        2 472.896    36.0
#> 69         0         1          1           3        3 419.775    36.0
#> 75         0         1          1           3        7 455.183    36.1
#> 82         0         1          0           0        1 455.183    36.1
#> 100        0         1          0           0        2 472.896    36.0
#>     PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 2          1.2             25000       0      65           3             2
#> 7          1.2             15000       0      65           3             4
#> 22         1.2             15000       0      65           3             2
#> 30         1.2             15000       0      65           3             2
#> 45         1.2             25000       0      65           3             2
#> 46         1.2             12000       0      65           2             2
#> 66         1.2             15000       0      65           3             2
#> 69         1.2             15000       0      65           3             1
#> 75         1.3             10000       0      74           3             1
#> 82         1.3             10000       0      74           3             1
#> 100        1.2             15000       0      65           3             2
#>     PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 2          209   1921.000       10        0    1300.000    209.0000
#> 7          209   1722.000       10        0    1459.500    214.0000
#> 22         209   1736.696       12        0     800.000    209.0000
#> 30         209   1753.000       10        1     658.000    205.0000
#> 45         209   1722.000       10        0    1546.000    209.0000
#> 46         209   1753.000       10        1     951.000    209.0000
#> 66         209   1935.700       10        1    1373.090    215.7700
#> 69         209   1722.000       10        1    1400.000    203.0000
#> 75         208   1850.696       10        1    1695.700    217.9990
#> 82         208   1850.696       10        1    1695.696    217.9994
#> 100        209   1921.000       10        0    1600.000    210.0000
#>     IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES IPR_PI       GEO_THMD
#> 2       1581.5  70.00       973.7       956.000  1.150        0|1744|
#> 7       3676.0  90.00       560.0       981.644  1.018    14.52|1954|
#> 22       557.0   8.00       568.0       364.696  2.300      0|1254.8|
#> 30      1500.0  53.82       210.4       440.962  0.800 0|1000|1541.4|
#> 45      1435.0  80.00         0.0         0.000  3.000     0|1667.08|
#> 46      3108.0  80.00       580.0       718.604  1.270      0|2263.7|
#> 66       762.0  60.00      1179.3      1031.980  4.400   0|2252|2580|
#> 69      1625.9  80.00      1141.6       758.608  2.590        0|1663|
#> 75       700.0   2.00      1075.0       736.188  1.550     0|5141.08|
#> 82       850.0  50.69      1082.2       589.100  1.400     0|7372.05|
#> 100     1009.0  80.00       784.6      1043.270  1.471        0|1593|
#>                GEO_THTEMP GL_method
#> 2                 90|200|         0
#> 7                 92|214|         0
#> 22                60|203|         0
#> 30       80|169.54|211.9|         2
#> 45                90|209|         0
#> 46                70|209|         0
#> 66  81.446|207.78|217.64|         2
#> 69                85|212|         2
#> 75               104|218|         2
#> 82           60.0001|206|         2
#> 100               80|224|         0
#>                                       GL_ArrayMandrels GL_Vdepth GL_GSG
#> 2                614.3|1118|1422.5|1564.6|0|0|0|0|0|0|   1564.60    1.2
#> 7    676.82|1099.42|1444.92|1675.82|1731.22|0|0|0|0|0|   1675.82    1.2
#> 22                             1139|0|0|0|0|0|0|0|0|0|    603.50    1.2
#> 30          583.9|872.3|1083.72|1246.9|1362|0|0|0|0|0|      0.00    1.2
#> 45  187.513|298.948|378.287|436.992|480.974|0|0|0|0|0|   1241.10    1.2
#> 46               683.6|1384|1891.4|2044.8|0|0|0|0|0|0|   2030.50    1.2
#> 66        808.4|1423.9|1834.9|2175.7|2252.5|0|0|0|0|0|      0.00    1.2
#> 69                    304|546|799|1058|1322|0|0|0|0|0|    284.00    1.2
#> 75   1532.15|2408.14|3133.2|3697.51|4501.31|0|0|0|0|0|   4501.31    1.2
#> 82                     2454.4|4285.43|0|0|0|0|0|0|0|0|   4284.78    1.2
#> 100                  569|865|1094|1276|1424|0|0|0|0|0|   1404.00    1.2
#>     GL_CO2
#> 2       65
#> 7       65
#> 22      65
#> 30      65
#> 45      65
#> 46      65
#> 66      65
#> 69      65
#> 75      65
#> 82      65
#> 100     65
#>                                                                                                                                                                                                                                                WT_DATE
#> 2   09/06/2014|21/08/2014|06/02/2012|17/03/2012|11/07/2012|10/08/2012|03/09/2012|05/10/2012|18/11/2012|22/01/2013|11/03/2013|10/04/2013|18/06/2013|04/07/2013|30/07/2013|23/09/2013|14/10/2013|10/11/2013|18/04/2014|21/07/2014|21/08/2014|06/09/2014|
#> 7                                                                                                                                                                                                                    05/05/2014|13/04/2014|17/12/2013|
#> 22                                                                                                                           17/01/2014|01/02/2014|01/03/2014|02/04/2014|09/05/2014|03/07/2014|26/08/2014|28/08/2014|04/09/2014|07/10/2014|05/11/2014|
#> 30                                                                                                                                                                                                                              12/03/2001|17/07/2000|
#> 45                                                                               06/04/2013|18/06/2013|06/07/2013|26/08/2013|16/09/2013|08/11/2013|08/11/2013|08/11/2013|12/04/2014|18/06/2014|21/08/2014|30/08/2014|12/09/2014|22/11/2014|30/12/2014|
#> 46                                                                                                                                                                                                                                        |09/02/2014|
#> 66                                                                                                                                                                                                                              18/05/2013|23/12/2014|
#> 69                                                                                                                                                                                                                   14/09/2014|22/11/2014|09/12/2014|
#> 75                                                                                                                                                                       21/11/2013|15/04/2014|04/05/2014|12/06/2014|15/04/2014|15/01/2015|15/01/2015|
#> 82                                                                                                                                                                                                                                               42005
#> 100                                                                                                                                                                                                                             07/09/2014|13/07/2014|
#>                                                                                       WT_THT
#> 2   125|125|125|125|135|125|125|127|125|125|125|125|125|125|125|125|125|125|125|125|125|122|
#> 7                                                                             125.6|125|125|
#> 22                                                         68|72|70|78|72|68|78|78|70|67|93|
#> 30                                                                                   110|96|
#> 45                              120|120|120|120|120|120|120|120|120|120|120|120|120|120|153|
#> 46                                                                                  130|114|
#> 66                                                                                  165|135|
#> 69                                                                              145|135|135|
#> 75                                                          114.8|149|149|141|110|154.4|140|
#> 82                                                                             109.400009155
#> 100                                                                                 125|143|
#>                                                                                                                             WT_LIQRT
#> 2   560|528|711.2|790.6|973.7|732.4|402.5|747.8|793.5|958.9|1190.5|1135.3|909.1|1006.4|980|1013.9|550.6|551.7|591.3|528.3|528.3|560|
#> 7                                                                                                                       560|558|558|
#> 22                                                                                      416|521|452|595|443|458|574|542|514|428|568|
#> 30                                                                                                                      527.7|210.4|
#> 45                                    1782.8|1197.9|1175.4|1586.8|1175.4|1174|1824|1805.4|133.7|772.9|1000.8|1000|1220.9|888.4|1342|
#> 46                                                                                                                          968|580|
#> 66                                                                                                                    2253.2|1179.3|
#> 69                                                                                                             1420.9|1074.3|1141.6|
#> 75                                                                                              339|1261|687|1075|212|1159.1|1159.1|
#> 82                                                                                                                    1082.199951172
#> 100                                                                                                                      784.6|1200|
#>                                                                                                                          WT_WC
#> 2   70|68|65.94|80.83|75.97|74.75|75.96|75.97|73.09|77.8|76.95|76.94|61.26|75.97|71.09|71.09|71.11|71.1|67.31|68.5|68.5|70.01|
#> 7                                                                                                                    90|90|90|
#> 22                                                                                                     0|0|0|5|5|7|8|10|8|7|8|
#> 30                                                                                                                 5.08|53.82|
#> 45                                              90.45|85.89|85.64|80.83|85.64|85.69|79.99|80.83|79.94|83.34|80|80|85.01|80|80|
#> 46                                                                                                                      85|80|
#> 66                                                                                                                      60|60|
#> 69                                                                                                                80|80.01|80|
#> 75                                                                                                       2|0.9|14|0|2|4.9|4.9|
#> 82                                                                                                                50.689998627
#> 100                                                                                                                     80|80|
#>                                                                                                                        WT_THP
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 7                                                                                                                261|290|290|
#> 22                                                                            101.5|101.53|101.5|261|87|80|87|101.5|87|87|87|
#> 30                                                                                                                 101.5|102|
#> 45                                           217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 46                                                                                                                 239|188.6|
#> 66                                                                                                                 246.6|232|
#> 69                                                                                                         217.6|217.6|217.5|
#> 75                                                                   173.696|214.696|188.696|246.696|269.696|217.696|217.696|
#> 82                                                                                                              122.395996948
#> 100                                                                                                                  290|522|
#>                                                                                                                                              WT_GOR
#> 2   4160|3974|1624.7|336.5|1581.5|287.5|1581|1581.8|1053|1265.5|1265.9|1160.1|759.6|1160.2|1160.1|1632.6|2974.1|4081.5|1759.7|3974.1|3974.1|3831.9|
#> 7                                                                                                                                   1233|1472|3676|
#> 22                                                                                                     696|554|645|421|614|398|458|652|186|534|557|
#> 30                                                                                                                                        977|1500|
#> 45                                            5763.4|2132.7|1532.9|718.3|2392.9|5214.8|2466.9|1462.2|3358|5126.2|1090.9|3321.9|583.3|1254.6|1435.2|
#> 46                                                                                                                                        375|3108|
#> 66                                                                                                                                     2368.52|762|
#> 69                                                                                                                              1530|1469.3|1625.9|
#> 75                                                                                                                    2626|586|950|700|500|660|500|
#> 82                                                                                                                                              850
#> 100                                                                                                                                      1009|2378|
#>                                                                                         WT_GLIR
#> 2   0.5|0.6|0.1|0.1|0.25|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.265|
#> 7                                                                                0.28|0.1|0.33|
#> 22                                      0.459|0.465|0.44|0.52|0.58|0.37|0.509|0.5|0.35|0.3|0.3|
#> 30                                                                                     0.6|0.1|
#> 45                                0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.27|
#> 46                                                                                    0.4|0.18|
#> 66                                                                                   0.19|0.24|
#> 69                                                                                 0.2|0.2|0.2|
#> 75                                                           0.04|0.6|0.56|0.75|0.06|0.48|0.35|
#> 82                                                                                  0.280000001
#> 100                                                                                    0.2|0.2|
#>                                                                                                                                                       WT_DEPTH
#> 2   1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|
#> 7                                                                                                                                     1675.82|1675.82|1675.82|
#> 22                                                                                          603.5|603.5|603.5|603.5|603.5|603.5|603.5|603.5|603.5|603.5|603.5|
#> 30                                                                                                                                                  1362|1362|
#> 45                                                   1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|
#> 46                                                                                                                                               683.6|2030.5|
#> 66                                                                                                                                              2252.5|2252.5|
#> 69                                                                                                                                             1322|1322|1322|
#> 75                                                                                                    4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|
#> 82                                                                                                                                              4285.433105469
#> 100                                                                                                                                                 1404|1404|
#>                                        WT_Enable
#> 2   1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 7                                         1|1|0|
#> 22                        1|1|1|1|1|1|1|1|1|1|0|
#> 30                                          1|0|
#> 45                1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 46                                          1|0|
#> 66                                          1|0|
#> 69                                        1|1|0|
#> 75                                1|1|1|1|1|1|0|
#> 82                                             0
#> 100                                         0|1|
#>                                        WT_GDEPTH
#> 2   0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 7                                         0|0|0|
#> 22                        0|0|0|0|0|0|0|0|0|0|0|
#> 30                                          0|0|
#> 45                0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 46                                       2258|0|
#> 66                                2517.8|2517.9|
#> 69                                        0|0|0|
#> 75              0|0|0|5141.08|5141.08|0|5141.08|
#> 82                                7372.047363281
#> 100                                         0|0|
#>                                                                                                                      WT_GPRES
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 7                                                                                                                261|290|290|
#> 22                                                                            101.5|101.53|101.5|261|87|80|87|101.5|87|87|87|
#> 30                                                                                                                 101.5|102|
#> 45                                           217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 46                                                                                                                1441|188.6|
#> 66                                                                                                            1211.51|1047.2|
#> 69                                                                                                         217.6|217.6|217.5|
#> 75                                                                   173.696|214.696|188.696|736.188|738.696|217.696|584.258|
#> 82                                                                                                              589.099991699
#> 100                                                                                                                  290|522|
#>                                                                                                         WT_RESPRES
#> 2   1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|
#> 7                                                                                            1459.5|1459.5|1459.5|
#> 22                                                                    600|600|600|600|600|600|600|600|600|600|800|
#> 30                                                                                                        658|658|
#> 45                                     1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|
#> 46                                                                                                       1700|951|
#> 66                                                                                                   1373.09|1373|
#> 69                                                                                                 1400|1400|1400|
#> 75                                                               1714.7|1698.7|1695.7|1695.7|1695.7|1695.7|1695.7|
#> 82                                                                                                        1695.696
#> 100                                                                                                     1600|1600|
#>                                            ProsperFilename
#> 2       \\\\network\\piscis\\well_models\\PISC-M007-TS.Out
#> 7       \\\\network\\piscis\\well_models\\PISC-M016-LS.Out
#> 22      \\\\network\\piscis\\well_models\\PISC-Q001-SS.Out
#> 30      \\\\network\\piscis\\well_models\\PISC-Q019-LS.Out
#> 45      \\\\network\\piscis\\well_models\\PISC-R009-SS.Out
#> 46      \\\\network\\piscis\\well_models\\PISC-R015-LS.Out
#> 66      \\\\network\\piscis\\well_models\\PISC-R027-LS.Out
#> 69  \\\\network\\piscis\\well_models\\PISC-R022ST02-TS.Out
#> 75         \\\\network\\piscis\\well_models\\PISC-S027.Out
#> 82      \\\\network\\piscis\\well_models\\PISC-S019-LS.Out
#> 100  \\\\network\\piscis\\well_models\\PISC-M026S01-TS.Out
```

The result is that we get the observations (rows) that have incorrect well names. They are 11 instances. This is much better than visually inspecting them in a spreadsheet, isn't it?

What are the type of offences?

-   Incorrect well number: PSCO-M0007-TS, PSCO-M0026-TS
-   Platform omitted: PSCO-027-TS
-   Platform in lowercase: PSCO-r015-LS, PSCO-m016-LS
-   Incorrect field name: PiSCO-R009-SS, PISCO-R027-LS
-   Incorrect completion type: PSCO-R022-T, PSCO-Q019-L, PSCO-Q001-S
-   Extra spaces in the name: PSCO-S019 -LS

Fix the well name
-----------------

Some can be fixed manually and other can be done automatically with a script. In our particular case we only have 100 wells but what about if we have 1000, or 5000? Doin,g it manually is not an option. Some are quickyly fixable some others are more challenging. Let's start by the easier ones.

Always go from the more general to the more particular.

``` r
# lowercase to uppercase
  myXl$Wellname <- toupper(myXl$Wellname)

# show the wells with issues
  myXl[!grepl("PSCO-[M,O,P,,Q,R,S][0-9][0-9][0-9]-[T,L,S]S", myXl$Wellname),]
#>          Wellname       Company  Analyst Field Location Platform Fluid
#> 2   PSCO-M0007-TS Oil Gains Co.     Aida PISCO  M007-TS        M     0
#> 22    PSCO-Q001-S Oil Gains Co.  Americo PISCO  Q001-SS        Q     0
#> 30    PSCO-Q019-L Oil Gains Co.   Norman PISCO  Q019-LS        Q     0
#> 45  PISCO-R009-SS Oil Gains Co.     Aida PISCO  R009-SS        R     0
#> 66  PISCO-R027-LS Oil Gains Co.   Norman PISCO  R027-LS        R     0
#> 69    PSCO-R022-T Oil Gains Co.   Norman PISCO  R022-TS        R     0
#> 75    PSCO-027-TS Oil Gains Co.   Andrew PISCO  S027-TS        S     0
#> 82  PSCO-S019 -LS Oil Gains Co.   Andrew PISCO  S019-LS        S     0
#> 100 PSCO-M0026-TS Oil Gains Co. Ibironke PISCO  M026-TS     <NA>     0
#>     WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 2          0         1          0           0       22 473.000    36.0
#> 22         0         1          0           0       11 420.000    36.0
#> 30         0         1          0           0        2 415.875    36.0
#> 45         0         1          0           0       15 420.000    36.0
#> 66         0         1          0           0        2 472.896    36.0
#> 69         0         1          1           3        3 419.775    36.0
#> 75         0         1          1           3        7 455.183    36.1
#> 82         0         1          0           0        1 455.183    36.1
#> 100        0         1          0           0        2 472.896    36.0
#>     PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 2          1.2             25000       0      65           3             2
#> 22         1.2             15000       0      65           3             2
#> 30         1.2             15000       0      65           3             2
#> 45         1.2             25000       0      65           3             2
#> 66         1.2             15000       0      65           3             2
#> 69         1.2             15000       0      65           3             1
#> 75         1.3             10000       0      74           3             1
#> 82         1.3             10000       0      74           3             1
#> 100        1.2             15000       0      65           3             2
#>     PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 2          209   1921.000       10        0    1300.000    209.0000
#> 22         209   1736.696       12        0     800.000    209.0000
#> 30         209   1753.000       10        1     658.000    205.0000
#> 45         209   1722.000       10        0    1546.000    209.0000
#> 66         209   1935.700       10        1    1373.090    215.7700
#> 69         209   1722.000       10        1    1400.000    203.0000
#> 75         208   1850.696       10        1    1695.700    217.9990
#> 82         208   1850.696       10        1    1695.696    217.9994
#> 100        209   1921.000       10        0    1600.000    210.0000
#>     IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES IPR_PI       GEO_THMD
#> 2       1581.5  70.00       973.7       956.000  1.150        0|1744|
#> 22       557.0   8.00       568.0       364.696  2.300      0|1254.8|
#> 30      1500.0  53.82       210.4       440.962  0.800 0|1000|1541.4|
#> 45      1435.0  80.00         0.0         0.000  3.000     0|1667.08|
#> 66       762.0  60.00      1179.3      1031.980  4.400   0|2252|2580|
#> 69      1625.9  80.00      1141.6       758.608  2.590        0|1663|
#> 75       700.0   2.00      1075.0       736.188  1.550     0|5141.08|
#> 82       850.0  50.69      1082.2       589.100  1.400     0|7372.05|
#> 100     1009.0  80.00       784.6      1043.270  1.471        0|1593|
#>                GEO_THTEMP GL_method
#> 2                 90|200|         0
#> 22                60|203|         0
#> 30       80|169.54|211.9|         2
#> 45                90|209|         0
#> 66  81.446|207.78|217.64|         2
#> 69                85|212|         2
#> 75               104|218|         2
#> 82           60.0001|206|         2
#> 100               80|224|         0
#>                                       GL_ArrayMandrels GL_Vdepth GL_GSG
#> 2                614.3|1118|1422.5|1564.6|0|0|0|0|0|0|   1564.60    1.2
#> 22                             1139|0|0|0|0|0|0|0|0|0|    603.50    1.2
#> 30          583.9|872.3|1083.72|1246.9|1362|0|0|0|0|0|      0.00    1.2
#> 45  187.513|298.948|378.287|436.992|480.974|0|0|0|0|0|   1241.10    1.2
#> 66        808.4|1423.9|1834.9|2175.7|2252.5|0|0|0|0|0|      0.00    1.2
#> 69                    304|546|799|1058|1322|0|0|0|0|0|    284.00    1.2
#> 75   1532.15|2408.14|3133.2|3697.51|4501.31|0|0|0|0|0|   4501.31    1.2
#> 82                     2454.4|4285.43|0|0|0|0|0|0|0|0|   4284.78    1.2
#> 100                  569|865|1094|1276|1424|0|0|0|0|0|   1404.00    1.2
#>     GL_CO2
#> 2       65
#> 22      65
#> 30      65
#> 45      65
#> 66      65
#> 69      65
#> 75      65
#> 82      65
#> 100     65
#>                                                                                                                                                                                                                                                WT_DATE
#> 2   09/06/2014|21/08/2014|06/02/2012|17/03/2012|11/07/2012|10/08/2012|03/09/2012|05/10/2012|18/11/2012|22/01/2013|11/03/2013|10/04/2013|18/06/2013|04/07/2013|30/07/2013|23/09/2013|14/10/2013|10/11/2013|18/04/2014|21/07/2014|21/08/2014|06/09/2014|
#> 22                                                                                                                           17/01/2014|01/02/2014|01/03/2014|02/04/2014|09/05/2014|03/07/2014|26/08/2014|28/08/2014|04/09/2014|07/10/2014|05/11/2014|
#> 30                                                                                                                                                                                                                              12/03/2001|17/07/2000|
#> 45                                                                               06/04/2013|18/06/2013|06/07/2013|26/08/2013|16/09/2013|08/11/2013|08/11/2013|08/11/2013|12/04/2014|18/06/2014|21/08/2014|30/08/2014|12/09/2014|22/11/2014|30/12/2014|
#> 66                                                                                                                                                                                                                              18/05/2013|23/12/2014|
#> 69                                                                                                                                                                                                                   14/09/2014|22/11/2014|09/12/2014|
#> 75                                                                                                                                                                       21/11/2013|15/04/2014|04/05/2014|12/06/2014|15/04/2014|15/01/2015|15/01/2015|
#> 82                                                                                                                                                                                                                                               42005
#> 100                                                                                                                                                                                                                             07/09/2014|13/07/2014|
#>                                                                                       WT_THT
#> 2   125|125|125|125|135|125|125|127|125|125|125|125|125|125|125|125|125|125|125|125|125|122|
#> 22                                                         68|72|70|78|72|68|78|78|70|67|93|
#> 30                                                                                   110|96|
#> 45                              120|120|120|120|120|120|120|120|120|120|120|120|120|120|153|
#> 66                                                                                  165|135|
#> 69                                                                              145|135|135|
#> 75                                                          114.8|149|149|141|110|154.4|140|
#> 82                                                                             109.400009155
#> 100                                                                                 125|143|
#>                                                                                                                             WT_LIQRT
#> 2   560|528|711.2|790.6|973.7|732.4|402.5|747.8|793.5|958.9|1190.5|1135.3|909.1|1006.4|980|1013.9|550.6|551.7|591.3|528.3|528.3|560|
#> 22                                                                                      416|521|452|595|443|458|574|542|514|428|568|
#> 30                                                                                                                      527.7|210.4|
#> 45                                    1782.8|1197.9|1175.4|1586.8|1175.4|1174|1824|1805.4|133.7|772.9|1000.8|1000|1220.9|888.4|1342|
#> 66                                                                                                                    2253.2|1179.3|
#> 69                                                                                                             1420.9|1074.3|1141.6|
#> 75                                                                                              339|1261|687|1075|212|1159.1|1159.1|
#> 82                                                                                                                    1082.199951172
#> 100                                                                                                                      784.6|1200|
#>                                                                                                                          WT_WC
#> 2   70|68|65.94|80.83|75.97|74.75|75.96|75.97|73.09|77.8|76.95|76.94|61.26|75.97|71.09|71.09|71.11|71.1|67.31|68.5|68.5|70.01|
#> 22                                                                                                     0|0|0|5|5|7|8|10|8|7|8|
#> 30                                                                                                                 5.08|53.82|
#> 45                                              90.45|85.89|85.64|80.83|85.64|85.69|79.99|80.83|79.94|83.34|80|80|85.01|80|80|
#> 66                                                                                                                      60|60|
#> 69                                                                                                                80|80.01|80|
#> 75                                                                                                       2|0.9|14|0|2|4.9|4.9|
#> 82                                                                                                                50.689998627
#> 100                                                                                                                     80|80|
#>                                                                                                                        WT_THP
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 22                                                                            101.5|101.53|101.5|261|87|80|87|101.5|87|87|87|
#> 30                                                                                                                 101.5|102|
#> 45                                           217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                                                                 246.6|232|
#> 69                                                                                                         217.6|217.6|217.5|
#> 75                                                                   173.696|214.696|188.696|246.696|269.696|217.696|217.696|
#> 82                                                                                                              122.395996948
#> 100                                                                                                                  290|522|
#>                                                                                                                                              WT_GOR
#> 2   4160|3974|1624.7|336.5|1581.5|287.5|1581|1581.8|1053|1265.5|1265.9|1160.1|759.6|1160.2|1160.1|1632.6|2974.1|4081.5|1759.7|3974.1|3974.1|3831.9|
#> 22                                                                                                     696|554|645|421|614|398|458|652|186|534|557|
#> 30                                                                                                                                        977|1500|
#> 45                                            5763.4|2132.7|1532.9|718.3|2392.9|5214.8|2466.9|1462.2|3358|5126.2|1090.9|3321.9|583.3|1254.6|1435.2|
#> 66                                                                                                                                     2368.52|762|
#> 69                                                                                                                              1530|1469.3|1625.9|
#> 75                                                                                                                    2626|586|950|700|500|660|500|
#> 82                                                                                                                                              850
#> 100                                                                                                                                      1009|2378|
#>                                                                                         WT_GLIR
#> 2   0.5|0.6|0.1|0.1|0.25|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.265|
#> 22                                      0.459|0.465|0.44|0.52|0.58|0.37|0.509|0.5|0.35|0.3|0.3|
#> 30                                                                                     0.6|0.1|
#> 45                                0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.27|
#> 66                                                                                   0.19|0.24|
#> 69                                                                                 0.2|0.2|0.2|
#> 75                                                           0.04|0.6|0.56|0.75|0.06|0.48|0.35|
#> 82                                                                                  0.280000001
#> 100                                                                                    0.2|0.2|
#>                                                                                                                                                       WT_DEPTH
#> 2   1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|
#> 22                                                                                          603.5|603.5|603.5|603.5|603.5|603.5|603.5|603.5|603.5|603.5|603.5|
#> 30                                                                                                                                                  1362|1362|
#> 45                                                   1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|
#> 66                                                                                                                                              2252.5|2252.5|
#> 69                                                                                                                                             1322|1322|1322|
#> 75                                                                                                    4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|
#> 82                                                                                                                                              4285.433105469
#> 100                                                                                                                                                 1404|1404|
#>                                        WT_Enable
#> 2   1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 22                        1|1|1|1|1|1|1|1|1|1|0|
#> 30                                          1|0|
#> 45                1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 66                                          1|0|
#> 69                                        1|1|0|
#> 75                                1|1|1|1|1|1|0|
#> 82                                             0
#> 100                                         0|1|
#>                                        WT_GDEPTH
#> 2   0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 22                        0|0|0|0|0|0|0|0|0|0|0|
#> 30                                          0|0|
#> 45                0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 66                                2517.8|2517.9|
#> 69                                        0|0|0|
#> 75              0|0|0|5141.08|5141.08|0|5141.08|
#> 82                                7372.047363281
#> 100                                         0|0|
#>                                                                                                                      WT_GPRES
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 22                                                                            101.5|101.53|101.5|261|87|80|87|101.5|87|87|87|
#> 30                                                                                                                 101.5|102|
#> 45                                           217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                                                            1211.51|1047.2|
#> 69                                                                                                         217.6|217.6|217.5|
#> 75                                                                   173.696|214.696|188.696|736.188|738.696|217.696|584.258|
#> 82                                                                                                              589.099991699
#> 100                                                                                                                  290|522|
#>                                                                                                         WT_RESPRES
#> 2   1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|
#> 22                                                                    600|600|600|600|600|600|600|600|600|600|800|
#> 30                                                                                                        658|658|
#> 45                                     1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|
#> 66                                                                                                   1373.09|1373|
#> 69                                                                                                 1400|1400|1400|
#> 75                                                               1714.7|1698.7|1695.7|1695.7|1695.7|1695.7|1695.7|
#> 82                                                                                                        1695.696
#> 100                                                                                                     1600|1600|
#>                                            ProsperFilename
#> 2       \\\\network\\piscis\\well_models\\PISC-M007-TS.Out
#> 22      \\\\network\\piscis\\well_models\\PISC-Q001-SS.Out
#> 30      \\\\network\\piscis\\well_models\\PISC-Q019-LS.Out
#> 45      \\\\network\\piscis\\well_models\\PISC-R009-SS.Out
#> 66      \\\\network\\piscis\\well_models\\PISC-R027-LS.Out
#> 69  \\\\network\\piscis\\well_models\\PISC-R022ST02-TS.Out
#> 75         \\\\network\\piscis\\well_models\\PISC-S027.Out
#> 82      \\\\network\\piscis\\well_models\\PISC-S019-LS.Out
#> 100  \\\\network\\piscis\\well_models\\PISC-M026S01-TS.Out
```

``` r
# removing spaces
  myXl$Wellname <- gsub(" ", "", myXl$Wellname)

# show the wells with issues
  myXl[!grepl("PSCO-[M,O,P,,Q,R,S][0-9][0-9][0-9]-[T,L,S]S", myXl$Wellname),]
#>          Wellname       Company  Analyst Field Location Platform Fluid
#> 2   PSCO-M0007-TS Oil Gains Co.     Aida PISCO  M007-TS        M     0
#> 22    PSCO-Q001-S Oil Gains Co.  Americo PISCO  Q001-SS        Q     0
#> 30    PSCO-Q019-L Oil Gains Co.   Norman PISCO  Q019-LS        Q     0
#> 45  PISCO-R009-SS Oil Gains Co.     Aida PISCO  R009-SS        R     0
#> 66  PISCO-R027-LS Oil Gains Co.   Norman PISCO  R027-LS        R     0
#> 69    PSCO-R022-T Oil Gains Co.   Norman PISCO  R022-TS        R     0
#> 75    PSCO-027-TS Oil Gains Co.   Andrew PISCO  S027-TS        S     0
#> 100 PSCO-M0026-TS Oil Gains Co. Ibironke PISCO  M026-TS     <NA>     0
#>     WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 2          0         1          0           0       22 473.000    36.0
#> 22         0         1          0           0       11 420.000    36.0
#> 30         0         1          0           0        2 415.875    36.0
#> 45         0         1          0           0       15 420.000    36.0
#> 66         0         1          0           0        2 472.896    36.0
#> 69         0         1          1           3        3 419.775    36.0
#> 75         0         1          1           3        7 455.183    36.1
#> 100        0         1          0           0        2 472.896    36.0
#>     PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 2          1.2             25000       0      65           3             2
#> 22         1.2             15000       0      65           3             2
#> 30         1.2             15000       0      65           3             2
#> 45         1.2             25000       0      65           3             2
#> 66         1.2             15000       0      65           3             2
#> 69         1.2             15000       0      65           3             1
#> 75         1.3             10000       0      74           3             1
#> 100        1.2             15000       0      65           3             2
#>     PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 2          209   1921.000       10        0     1300.00     209.000
#> 22         209   1736.696       12        0      800.00     209.000
#> 30         209   1753.000       10        1      658.00     205.000
#> 45         209   1722.000       10        0     1546.00     209.000
#> 66         209   1935.700       10        1     1373.09     215.770
#> 69         209   1722.000       10        1     1400.00     203.000
#> 75         208   1850.696       10        1     1695.70     217.999
#> 100        209   1921.000       10        0     1600.00     210.000
#>     IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES IPR_PI       GEO_THMD
#> 2       1581.5  70.00       973.7       956.000  1.150        0|1744|
#> 22       557.0   8.00       568.0       364.696  2.300      0|1254.8|
#> 30      1500.0  53.82       210.4       440.962  0.800 0|1000|1541.4|
#> 45      1435.0  80.00         0.0         0.000  3.000     0|1667.08|
#> 66       762.0  60.00      1179.3      1031.980  4.400   0|2252|2580|
#> 69      1625.9  80.00      1141.6       758.608  2.590        0|1663|
#> 75       700.0   2.00      1075.0       736.188  1.550     0|5141.08|
#> 100     1009.0  80.00       784.6      1043.270  1.471        0|1593|
#>                GEO_THTEMP GL_method
#> 2                 90|200|         0
#> 22                60|203|         0
#> 30       80|169.54|211.9|         2
#> 45                90|209|         0
#> 66  81.446|207.78|217.64|         2
#> 69                85|212|         2
#> 75               104|218|         2
#> 100               80|224|         0
#>                                       GL_ArrayMandrels GL_Vdepth GL_GSG
#> 2                614.3|1118|1422.5|1564.6|0|0|0|0|0|0|   1564.60    1.2
#> 22                             1139|0|0|0|0|0|0|0|0|0|    603.50    1.2
#> 30          583.9|872.3|1083.72|1246.9|1362|0|0|0|0|0|      0.00    1.2
#> 45  187.513|298.948|378.287|436.992|480.974|0|0|0|0|0|   1241.10    1.2
#> 66        808.4|1423.9|1834.9|2175.7|2252.5|0|0|0|0|0|      0.00    1.2
#> 69                    304|546|799|1058|1322|0|0|0|0|0|    284.00    1.2
#> 75   1532.15|2408.14|3133.2|3697.51|4501.31|0|0|0|0|0|   4501.31    1.2
#> 100                  569|865|1094|1276|1424|0|0|0|0|0|   1404.00    1.2
#>     GL_CO2
#> 2       65
#> 22      65
#> 30      65
#> 45      65
#> 66      65
#> 69      65
#> 75      65
#> 100     65
#>                                                                                                                                                                                                                                                WT_DATE
#> 2   09/06/2014|21/08/2014|06/02/2012|17/03/2012|11/07/2012|10/08/2012|03/09/2012|05/10/2012|18/11/2012|22/01/2013|11/03/2013|10/04/2013|18/06/2013|04/07/2013|30/07/2013|23/09/2013|14/10/2013|10/11/2013|18/04/2014|21/07/2014|21/08/2014|06/09/2014|
#> 22                                                                                                                           17/01/2014|01/02/2014|01/03/2014|02/04/2014|09/05/2014|03/07/2014|26/08/2014|28/08/2014|04/09/2014|07/10/2014|05/11/2014|
#> 30                                                                                                                                                                                                                              12/03/2001|17/07/2000|
#> 45                                                                               06/04/2013|18/06/2013|06/07/2013|26/08/2013|16/09/2013|08/11/2013|08/11/2013|08/11/2013|12/04/2014|18/06/2014|21/08/2014|30/08/2014|12/09/2014|22/11/2014|30/12/2014|
#> 66                                                                                                                                                                                                                              18/05/2013|23/12/2014|
#> 69                                                                                                                                                                                                                   14/09/2014|22/11/2014|09/12/2014|
#> 75                                                                                                                                                                       21/11/2013|15/04/2014|04/05/2014|12/06/2014|15/04/2014|15/01/2015|15/01/2015|
#> 100                                                                                                                                                                                                                             07/09/2014|13/07/2014|
#>                                                                                       WT_THT
#> 2   125|125|125|125|135|125|125|127|125|125|125|125|125|125|125|125|125|125|125|125|125|122|
#> 22                                                         68|72|70|78|72|68|78|78|70|67|93|
#> 30                                                                                   110|96|
#> 45                              120|120|120|120|120|120|120|120|120|120|120|120|120|120|153|
#> 66                                                                                  165|135|
#> 69                                                                              145|135|135|
#> 75                                                          114.8|149|149|141|110|154.4|140|
#> 100                                                                                 125|143|
#>                                                                                                                             WT_LIQRT
#> 2   560|528|711.2|790.6|973.7|732.4|402.5|747.8|793.5|958.9|1190.5|1135.3|909.1|1006.4|980|1013.9|550.6|551.7|591.3|528.3|528.3|560|
#> 22                                                                                      416|521|452|595|443|458|574|542|514|428|568|
#> 30                                                                                                                      527.7|210.4|
#> 45                                    1782.8|1197.9|1175.4|1586.8|1175.4|1174|1824|1805.4|133.7|772.9|1000.8|1000|1220.9|888.4|1342|
#> 66                                                                                                                    2253.2|1179.3|
#> 69                                                                                                             1420.9|1074.3|1141.6|
#> 75                                                                                              339|1261|687|1075|212|1159.1|1159.1|
#> 100                                                                                                                      784.6|1200|
#>                                                                                                                          WT_WC
#> 2   70|68|65.94|80.83|75.97|74.75|75.96|75.97|73.09|77.8|76.95|76.94|61.26|75.97|71.09|71.09|71.11|71.1|67.31|68.5|68.5|70.01|
#> 22                                                                                                     0|0|0|5|5|7|8|10|8|7|8|
#> 30                                                                                                                 5.08|53.82|
#> 45                                              90.45|85.89|85.64|80.83|85.64|85.69|79.99|80.83|79.94|83.34|80|80|85.01|80|80|
#> 66                                                                                                                      60|60|
#> 69                                                                                                                80|80.01|80|
#> 75                                                                                                       2|0.9|14|0|2|4.9|4.9|
#> 100                                                                                                                     80|80|
#>                                                                                                                        WT_THP
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 22                                                                            101.5|101.53|101.5|261|87|80|87|101.5|87|87|87|
#> 30                                                                                                                 101.5|102|
#> 45                                           217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                                                                 246.6|232|
#> 69                                                                                                         217.6|217.6|217.5|
#> 75                                                                   173.696|214.696|188.696|246.696|269.696|217.696|217.696|
#> 100                                                                                                                  290|522|
#>                                                                                                                                              WT_GOR
#> 2   4160|3974|1624.7|336.5|1581.5|287.5|1581|1581.8|1053|1265.5|1265.9|1160.1|759.6|1160.2|1160.1|1632.6|2974.1|4081.5|1759.7|3974.1|3974.1|3831.9|
#> 22                                                                                                     696|554|645|421|614|398|458|652|186|534|557|
#> 30                                                                                                                                        977|1500|
#> 45                                            5763.4|2132.7|1532.9|718.3|2392.9|5214.8|2466.9|1462.2|3358|5126.2|1090.9|3321.9|583.3|1254.6|1435.2|
#> 66                                                                                                                                     2368.52|762|
#> 69                                                                                                                              1530|1469.3|1625.9|
#> 75                                                                                                                    2626|586|950|700|500|660|500|
#> 100                                                                                                                                      1009|2378|
#>                                                                                         WT_GLIR
#> 2   0.5|0.6|0.1|0.1|0.25|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.265|
#> 22                                      0.459|0.465|0.44|0.52|0.58|0.37|0.509|0.5|0.35|0.3|0.3|
#> 30                                                                                     0.6|0.1|
#> 45                                0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.27|
#> 66                                                                                   0.19|0.24|
#> 69                                                                                 0.2|0.2|0.2|
#> 75                                                           0.04|0.6|0.56|0.75|0.06|0.48|0.35|
#> 100                                                                                    0.2|0.2|
#>                                                                                                                                                       WT_DEPTH
#> 2   1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|
#> 22                                                                                          603.5|603.5|603.5|603.5|603.5|603.5|603.5|603.5|603.5|603.5|603.5|
#> 30                                                                                                                                                  1362|1362|
#> 45                                                   1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|
#> 66                                                                                                                                              2252.5|2252.5|
#> 69                                                                                                                                             1322|1322|1322|
#> 75                                                                                                    4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|
#> 100                                                                                                                                                 1404|1404|
#>                                        WT_Enable
#> 2   1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 22                        1|1|1|1|1|1|1|1|1|1|0|
#> 30                                          1|0|
#> 45                1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 66                                          1|0|
#> 69                                        1|1|0|
#> 75                                1|1|1|1|1|1|0|
#> 100                                         0|1|
#>                                        WT_GDEPTH
#> 2   0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 22                        0|0|0|0|0|0|0|0|0|0|0|
#> 30                                          0|0|
#> 45                0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 66                                2517.8|2517.9|
#> 69                                        0|0|0|
#> 75              0|0|0|5141.08|5141.08|0|5141.08|
#> 100                                         0|0|
#>                                                                                                                      WT_GPRES
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 22                                                                            101.5|101.53|101.5|261|87|80|87|101.5|87|87|87|
#> 30                                                                                                                 101.5|102|
#> 45                                           217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                                                            1211.51|1047.2|
#> 69                                                                                                         217.6|217.6|217.5|
#> 75                                                                   173.696|214.696|188.696|736.188|738.696|217.696|584.258|
#> 100                                                                                                                  290|522|
#>                                                                                                         WT_RESPRES
#> 2   1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|
#> 22                                                                    600|600|600|600|600|600|600|600|600|600|800|
#> 30                                                                                                        658|658|
#> 45                                     1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|
#> 66                                                                                                   1373.09|1373|
#> 69                                                                                                 1400|1400|1400|
#> 75                                                               1714.7|1698.7|1695.7|1695.7|1695.7|1695.7|1695.7|
#> 100                                                                                                     1600|1600|
#>                                            ProsperFilename
#> 2       \\\\network\\piscis\\well_models\\PISC-M007-TS.Out
#> 22      \\\\network\\piscis\\well_models\\PISC-Q001-SS.Out
#> 30      \\\\network\\piscis\\well_models\\PISC-Q019-LS.Out
#> 45      \\\\network\\piscis\\well_models\\PISC-R009-SS.Out
#> 66      \\\\network\\piscis\\well_models\\PISC-R027-LS.Out
#> 69  \\\\network\\piscis\\well_models\\PISC-R022ST02-TS.Out
#> 75         \\\\network\\piscis\\well_models\\PISC-S027.Out
#> 100  \\\\network\\piscis\\well_models\\PISC-M026S01-TS.Out
```

``` r
# complete the completion type
# We have three completion type: SS, LS and TS

  myXl$Wellname <- gsub("-L$", "-LS", myXl$Wellname)    # the dollar sign at the end, means that 
  myXl$Wellname <- gsub("-S$", "-SS", myXl$Wellname)    # we are checking at the end of the string
  myXl$Wellname <- gsub("-T$", "-TS", myXl$Wellname)

# show the wells with issues
  myXl[!grepl("PSCO-[M,O,P,,Q,R,S][0-9][0-9][0-9]-[T,L,S]S", myXl$Wellname),]
#>          Wellname       Company  Analyst Field Location Platform Fluid
#> 2   PSCO-M0007-TS Oil Gains Co.     Aida PISCO  M007-TS        M     0
#> 45  PISCO-R009-SS Oil Gains Co.     Aida PISCO  R009-SS        R     0
#> 66  PISCO-R027-LS Oil Gains Co.   Norman PISCO  R027-LS        R     0
#> 75    PSCO-027-TS Oil Gains Co.   Andrew PISCO  S027-TS        S     0
#> 100 PSCO-M0026-TS Oil Gains Co. Ibironke PISCO  M026-TS     <NA>     0
#>     WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 2          0         1          0           0       22 473.000    36.0
#> 45         0         1          0           0       15 420.000    36.0
#> 66         0         1          0           0        2 472.896    36.0
#> 75         0         1          1           3        7 455.183    36.1
#> 100        0         1          0           0        2 472.896    36.0
#>     PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 2          1.2             25000       0      65           3             2
#> 45         1.2             25000       0      65           3             2
#> 66         1.2             15000       0      65           3             2
#> 75         1.3             10000       0      74           3             1
#> 100        1.2             15000       0      65           3             2
#>     PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 2          209   1921.000       10        0     1300.00     209.000
#> 45         209   1722.000       10        0     1546.00     209.000
#> 66         209   1935.700       10        1     1373.09     215.770
#> 75         208   1850.696       10        1     1695.70     217.999
#> 100        209   1921.000       10        0     1600.00     210.000
#>     IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES IPR_PI     GEO_THMD
#> 2       1581.5     70       973.7       956.000  1.150      0|1744|
#> 45      1435.0     80         0.0         0.000  3.000   0|1667.08|
#> 66       762.0     60      1179.3      1031.980  4.400 0|2252|2580|
#> 75       700.0      2      1075.0       736.188  1.550   0|5141.08|
#> 100     1009.0     80       784.6      1043.270  1.471      0|1593|
#>                GEO_THTEMP GL_method
#> 2                 90|200|         0
#> 45                90|209|         0
#> 66  81.446|207.78|217.64|         2
#> 75               104|218|         2
#> 100               80|224|         0
#>                                       GL_ArrayMandrels GL_Vdepth GL_GSG
#> 2                614.3|1118|1422.5|1564.6|0|0|0|0|0|0|   1564.60    1.2
#> 45  187.513|298.948|378.287|436.992|480.974|0|0|0|0|0|   1241.10    1.2
#> 66        808.4|1423.9|1834.9|2175.7|2252.5|0|0|0|0|0|      0.00    1.2
#> 75   1532.15|2408.14|3133.2|3697.51|4501.31|0|0|0|0|0|   4501.31    1.2
#> 100                  569|865|1094|1276|1424|0|0|0|0|0|   1404.00    1.2
#>     GL_CO2
#> 2       65
#> 45      65
#> 66      65
#> 75      65
#> 100     65
#>                                                                                                                                                                                                                                                WT_DATE
#> 2   09/06/2014|21/08/2014|06/02/2012|17/03/2012|11/07/2012|10/08/2012|03/09/2012|05/10/2012|18/11/2012|22/01/2013|11/03/2013|10/04/2013|18/06/2013|04/07/2013|30/07/2013|23/09/2013|14/10/2013|10/11/2013|18/04/2014|21/07/2014|21/08/2014|06/09/2014|
#> 45                                                                               06/04/2013|18/06/2013|06/07/2013|26/08/2013|16/09/2013|08/11/2013|08/11/2013|08/11/2013|12/04/2014|18/06/2014|21/08/2014|30/08/2014|12/09/2014|22/11/2014|30/12/2014|
#> 66                                                                                                                                                                                                                              18/05/2013|23/12/2014|
#> 75                                                                                                                                                                       21/11/2013|15/04/2014|04/05/2014|12/06/2014|15/04/2014|15/01/2015|15/01/2015|
#> 100                                                                                                                                                                                                                             07/09/2014|13/07/2014|
#>                                                                                       WT_THT
#> 2   125|125|125|125|135|125|125|127|125|125|125|125|125|125|125|125|125|125|125|125|125|122|
#> 45                              120|120|120|120|120|120|120|120|120|120|120|120|120|120|153|
#> 66                                                                                  165|135|
#> 75                                                          114.8|149|149|141|110|154.4|140|
#> 100                                                                                 125|143|
#>                                                                                                                             WT_LIQRT
#> 2   560|528|711.2|790.6|973.7|732.4|402.5|747.8|793.5|958.9|1190.5|1135.3|909.1|1006.4|980|1013.9|550.6|551.7|591.3|528.3|528.3|560|
#> 45                                    1782.8|1197.9|1175.4|1586.8|1175.4|1174|1824|1805.4|133.7|772.9|1000.8|1000|1220.9|888.4|1342|
#> 66                                                                                                                    2253.2|1179.3|
#> 75                                                                                              339|1261|687|1075|212|1159.1|1159.1|
#> 100                                                                                                                      784.6|1200|
#>                                                                                                                          WT_WC
#> 2   70|68|65.94|80.83|75.97|74.75|75.96|75.97|73.09|77.8|76.95|76.94|61.26|75.97|71.09|71.09|71.11|71.1|67.31|68.5|68.5|70.01|
#> 45                                              90.45|85.89|85.64|80.83|85.64|85.69|79.99|80.83|79.94|83.34|80|80|85.01|80|80|
#> 66                                                                                                                      60|60|
#> 75                                                                                                       2|0.9|14|0|2|4.9|4.9|
#> 100                                                                                                                     80|80|
#>                                                                                                                        WT_THP
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 45                                           217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                                                                 246.6|232|
#> 75                                                                   173.696|214.696|188.696|246.696|269.696|217.696|217.696|
#> 100                                                                                                                  290|522|
#>                                                                                                                                              WT_GOR
#> 2   4160|3974|1624.7|336.5|1581.5|287.5|1581|1581.8|1053|1265.5|1265.9|1160.1|759.6|1160.2|1160.1|1632.6|2974.1|4081.5|1759.7|3974.1|3974.1|3831.9|
#> 45                                            5763.4|2132.7|1532.9|718.3|2392.9|5214.8|2466.9|1462.2|3358|5126.2|1090.9|3321.9|583.3|1254.6|1435.2|
#> 66                                                                                                                                     2368.52|762|
#> 75                                                                                                                    2626|586|950|700|500|660|500|
#> 100                                                                                                                                      1009|2378|
#>                                                                                         WT_GLIR
#> 2   0.5|0.6|0.1|0.1|0.25|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.265|
#> 45                                0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.27|
#> 66                                                                                   0.19|0.24|
#> 75                                                           0.04|0.6|0.56|0.75|0.06|0.48|0.35|
#> 100                                                                                    0.2|0.2|
#>                                                                                                                                                       WT_DEPTH
#> 2   1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|
#> 45                                                   1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|
#> 66                                                                                                                                              2252.5|2252.5|
#> 75                                                                                                    4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|
#> 100                                                                                                                                                 1404|1404|
#>                                        WT_Enable
#> 2   1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 45                1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 66                                          1|0|
#> 75                                1|1|1|1|1|1|0|
#> 100                                         0|1|
#>                                        WT_GDEPTH
#> 2   0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 45                0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 66                                2517.8|2517.9|
#> 75              0|0|0|5141.08|5141.08|0|5141.08|
#> 100                                         0|0|
#>                                                                                                                      WT_GPRES
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 45                                           217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                                                            1211.51|1047.2|
#> 75                                                                   173.696|214.696|188.696|736.188|738.696|217.696|584.258|
#> 100                                                                                                                  290|522|
#>                                                                                                         WT_RESPRES
#> 2   1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|
#> 45                                     1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|
#> 66                                                                                                   1373.09|1373|
#> 75                                                               1714.7|1698.7|1695.7|1695.7|1695.7|1695.7|1695.7|
#> 100                                                                                                     1600|1600|
#>                                           ProsperFilename
#> 2      \\\\network\\piscis\\well_models\\PISC-M007-TS.Out
#> 45     \\\\network\\piscis\\well_models\\PISC-R009-SS.Out
#> 66     \\\\network\\piscis\\well_models\\PISC-R027-LS.Out
#> 75        \\\\network\\piscis\\well_models\\PISC-S027.Out
#> 100 \\\\network\\piscis\\well_models\\PISC-M026S01-TS.Out
```

Those were the easy ones. There are 5 more to go.

``` r
# detect well names that are not named as PSCO-
  myXl[!grepl("^PSCO-", myXl$Wellname), ]        # the ^ character means look at the start of the string
#>         Wellname       Company Analyst Field Location Platform Fluid
#> 45 PISCO-R009-SS Oil Gains Co.    Aida PISCO  R009-SS        R     0
#> 66 PISCO-R027-LS Oil Gains Co.  Norman PISCO  R027-LS        R     0
#>    WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 45        0         1          0           0       15 420.000      36
#> 66        0         1          0           0        2 472.896      36
#>    PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 45        1.2             25000       0      65           3             2
#> 66        1.2             15000       0      65           3             2
#>    PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 45        209     1722.0       10        0     1546.00      209.00
#> 66        209     1935.7       10        1     1373.09      215.77
#>    IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES IPR_PI     GEO_THMD
#> 45       1435     80         0.0          0.00    3.0   0|1667.08|
#> 66        762     60      1179.3       1031.98    4.4 0|2252|2580|
#>               GEO_THTEMP GL_method
#> 45               90|209|         0
#> 66 81.446|207.78|217.64|         2
#>                                      GL_ArrayMandrels GL_Vdepth GL_GSG
#> 45 187.513|298.948|378.287|436.992|480.974|0|0|0|0|0|    1241.1    1.2
#> 66       808.4|1423.9|1834.9|2175.7|2252.5|0|0|0|0|0|       0.0    1.2
#>    GL_CO2
#> 45     65
#> 66     65
#>                                                                                                                                                                  WT_DATE
#> 45 06/04/2013|18/06/2013|06/07/2013|26/08/2013|16/09/2013|08/11/2013|08/11/2013|08/11/2013|12/04/2014|18/06/2014|21/08/2014|30/08/2014|12/09/2014|22/11/2014|30/12/2014|
#> 66                                                                                                                                                18/05/2013|23/12/2014|
#>                                                          WT_THT
#> 45 120|120|120|120|120|120|120|120|120|120|120|120|120|120|153|
#> 66                                                     165|135|
#>                                                                                          WT_LIQRT
#> 45 1782.8|1197.9|1175.4|1586.8|1175.4|1174|1824|1805.4|133.7|772.9|1000.8|1000|1220.9|888.4|1342|
#> 66                                                                                 2253.2|1179.3|
#>                                                                             WT_WC
#> 45 90.45|85.89|85.64|80.83|85.64|85.69|79.99|80.83|79.94|83.34|80|80|85.01|80|80|
#> 66                                                                         60|60|
#>                                                                              WT_THP
#> 45 217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                       246.6|232|
#>                                                                                                   WT_GOR
#> 45 5763.4|2132.7|1532.9|718.3|2392.9|5214.8|2466.9|1462.2|3358|5126.2|1090.9|3321.9|583.3|1254.6|1435.2|
#> 66                                                                                          2368.52|762|
#>                                                          WT_GLIR
#> 45 0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.27|
#> 66                                                    0.19|0.24|
#>                                                                                                     WT_DEPTH
#> 45 1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|
#> 66                                                                                            2252.5|2252.5|
#>                         WT_Enable                      WT_GDEPTH
#> 45 1|1|1|1|1|1|1|1|1|1|1|1|1|1|0| 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 66                           1|0|                 2517.8|2517.9|
#>                                                                            WT_GPRES
#> 45 217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                  1211.51|1047.2|
#>                                                                     WT_RESPRES
#> 45 1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|
#> 66                                                               1373.09|1373|
#>                                       ProsperFilename
#> 45 \\\\network\\piscis\\well_models\\PISC-R009-SS.Out
#> 66 \\\\network\\piscis\\well_models\\PISC-R027-LS.Out
```

### 

``` r
# replace any characters before the first dash
  x <- myXl$Wellname

  pattern <- "^[^-]+"
  repl_with <- "PSCO"

  myXl$Wellname <- gsub(pattern, repl_with, x, perl = TRUE)

  # show the wells with issues
  myXl[!grepl("PSCO-[M,O,P,,Q,R,S][0-9][0-9][0-9]-[T,L,S]S", myXl$Wellname),]
#>          Wellname       Company  Analyst Field Location Platform Fluid
#> 2   PSCO-M0007-TS Oil Gains Co.     Aida PISCO  M007-TS        M     0
#> 75    PSCO-027-TS Oil Gains Co.   Andrew PISCO  S027-TS        S     0
#> 100 PSCO-M0026-TS Oil Gains Co. Ibironke PISCO  M026-TS     <NA>     0
#>     WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 2          0         1          0           0       22 473.000    36.0
#> 75         0         1          1           3        7 455.183    36.1
#> 100        0         1          0           0        2 472.896    36.0
#>     PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 2          1.2             25000       0      65           3             2
#> 75         1.3             10000       0      74           3             1
#> 100        1.2             15000       0      65           3             2
#>     PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 2          209   1921.000       10        0      1300.0     209.000
#> 75         208   1850.696       10        1      1695.7     217.999
#> 100        209   1921.000       10        0      1600.0     210.000
#>     IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES IPR_PI   GEO_THMD
#> 2       1581.5     70       973.7       956.000  1.150    0|1744|
#> 75       700.0      2      1075.0       736.188  1.550 0|5141.08|
#> 100     1009.0     80       784.6      1043.270  1.471    0|1593|
#>     GEO_THTEMP GL_method                                  GL_ArrayMandrels
#> 2      90|200|         0             614.3|1118|1422.5|1564.6|0|0|0|0|0|0|
#> 75    104|218|         2 1532.15|2408.14|3133.2|3697.51|4501.31|0|0|0|0|0|
#> 100    80|224|         0                 569|865|1094|1276|1424|0|0|0|0|0|
#>     GL_Vdepth GL_GSG GL_CO2
#> 2     1564.60    1.2     65
#> 75    4501.31    1.2     65
#> 100   1404.00    1.2     65
#>                                                                                                                                                                                                                                                WT_DATE
#> 2   09/06/2014|21/08/2014|06/02/2012|17/03/2012|11/07/2012|10/08/2012|03/09/2012|05/10/2012|18/11/2012|22/01/2013|11/03/2013|10/04/2013|18/06/2013|04/07/2013|30/07/2013|23/09/2013|14/10/2013|10/11/2013|18/04/2014|21/07/2014|21/08/2014|06/09/2014|
#> 75                                                                                                                                                                       21/11/2013|15/04/2014|04/05/2014|12/06/2014|15/04/2014|15/01/2015|15/01/2015|
#> 100                                                                                                                                                                                                                             07/09/2014|13/07/2014|
#>                                                                                       WT_THT
#> 2   125|125|125|125|135|125|125|127|125|125|125|125|125|125|125|125|125|125|125|125|125|122|
#> 75                                                          114.8|149|149|141|110|154.4|140|
#> 100                                                                                 125|143|
#>                                                                                                                             WT_LIQRT
#> 2   560|528|711.2|790.6|973.7|732.4|402.5|747.8|793.5|958.9|1190.5|1135.3|909.1|1006.4|980|1013.9|550.6|551.7|591.3|528.3|528.3|560|
#> 75                                                                                              339|1261|687|1075|212|1159.1|1159.1|
#> 100                                                                                                                      784.6|1200|
#>                                                                                                                          WT_WC
#> 2   70|68|65.94|80.83|75.97|74.75|75.96|75.97|73.09|77.8|76.95|76.94|61.26|75.97|71.09|71.09|71.11|71.1|67.31|68.5|68.5|70.01|
#> 75                                                                                                       2|0.9|14|0|2|4.9|4.9|
#> 100                                                                                                                     80|80|
#>                                                                                                                        WT_THP
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 75                                                                   173.696|214.696|188.696|246.696|269.696|217.696|217.696|
#> 100                                                                                                                  290|522|
#>                                                                                                                                              WT_GOR
#> 2   4160|3974|1624.7|336.5|1581.5|287.5|1581|1581.8|1053|1265.5|1265.9|1160.1|759.6|1160.2|1160.1|1632.6|2974.1|4081.5|1759.7|3974.1|3974.1|3831.9|
#> 75                                                                                                                    2626|586|950|700|500|660|500|
#> 100                                                                                                                                      1009|2378|
#>                                                                                         WT_GLIR
#> 2   0.5|0.6|0.1|0.1|0.25|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.265|
#> 75                                                           0.04|0.6|0.56|0.75|0.06|0.48|0.35|
#> 100                                                                                    0.2|0.2|
#>                                                                                                                                                       WT_DEPTH
#> 2   1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|
#> 75                                                                                                    4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|
#> 100                                                                                                                                                 1404|1404|
#>                                        WT_Enable
#> 2   1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 75                                1|1|1|1|1|1|0|
#> 100                                         0|1|
#>                                        WT_GDEPTH
#> 2   0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 75              0|0|0|5141.08|5141.08|0|5141.08|
#> 100                                         0|0|
#>                                                                                                                      WT_GPRES
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 75                                                                   173.696|214.696|188.696|736.188|738.696|217.696|584.258|
#> 100                                                                                                                  290|522|
#>                                                                                                         WT_RESPRES
#> 2   1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|
#> 75                                                               1714.7|1698.7|1695.7|1695.7|1695.7|1695.7|1695.7|
#> 100                                                                                                     1600|1600|
#>                                           ProsperFilename
#> 2      \\\\network\\piscis\\well_models\\PISC-M007-TS.Out
#> 75        \\\\network\\piscis\\well_models\\PISC-S027.Out
#> 100 \\\\network\\piscis\\well_models\\PISC-M026S01-TS.Out
```

Alright. We corrected the field name in the well name. There are still three more wells to go which problems are:

    PSCO-M0007-TS  long well number. It should be maximum of 3 digits
    PSCO-027-TS    missing platform number
    PSCO-M0026-TS  long well number. It should be maximum of 3 digits

### correcting longer well number (digits)

``` r
# find wells with longer well number
x <- myXl$Wellname
myXl[grepl("[0-9]{4}-", x, perl=TRUE), ]     # 
#>          Wellname       Company  Analyst Field Location Platform Fluid
#> 2   PSCO-M0007-TS Oil Gains Co.     Aida PISCO  M007-TS        M     0
#> 100 PSCO-M0026-TS Oil Gains Co. Ibironke PISCO  M026-TS     <NA>     0
#>     WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 2          0         1          0           0       22 473.000      36
#> 100        0         1          0           0        2 472.896      36
#>     PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 2          1.2             25000       0      65           3             2
#> 100        1.2             15000       0      65           3             2
#>     PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 2          209       1921       10        0        1300         209
#> 100        209       1921       10        0        1600         210
#>     IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES IPR_PI GEO_THMD GEO_THTEMP
#> 2       1581.5     70       973.7        956.00  1.150  0|1744|    90|200|
#> 100     1009.0     80       784.6       1043.27  1.471  0|1593|    80|224|
#>     GL_method                      GL_ArrayMandrels GL_Vdepth GL_GSG
#> 2           0 614.3|1118|1422.5|1564.6|0|0|0|0|0|0|    1564.6    1.2
#> 100         0     569|865|1094|1276|1424|0|0|0|0|0|    1404.0    1.2
#>     GL_CO2
#> 2       65
#> 100     65
#>                                                                                                                                                                                                                                                WT_DATE
#> 2   09/06/2014|21/08/2014|06/02/2012|17/03/2012|11/07/2012|10/08/2012|03/09/2012|05/10/2012|18/11/2012|22/01/2013|11/03/2013|10/04/2013|18/06/2013|04/07/2013|30/07/2013|23/09/2013|14/10/2013|10/11/2013|18/04/2014|21/07/2014|21/08/2014|06/09/2014|
#> 100                                                                                                                                                                                                                             07/09/2014|13/07/2014|
#>                                                                                       WT_THT
#> 2   125|125|125|125|135|125|125|127|125|125|125|125|125|125|125|125|125|125|125|125|125|122|
#> 100                                                                                 125|143|
#>                                                                                                                             WT_LIQRT
#> 2   560|528|711.2|790.6|973.7|732.4|402.5|747.8|793.5|958.9|1190.5|1135.3|909.1|1006.4|980|1013.9|550.6|551.7|591.3|528.3|528.3|560|
#> 100                                                                                                                      784.6|1200|
#>                                                                                                                          WT_WC
#> 2   70|68|65.94|80.83|75.97|74.75|75.96|75.97|73.09|77.8|76.95|76.94|61.26|75.97|71.09|71.09|71.11|71.1|67.31|68.5|68.5|70.01|
#> 100                                                                                                                     80|80|
#>                                                                                                                        WT_THP
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 100                                                                                                                  290|522|
#>                                                                                                                                              WT_GOR
#> 2   4160|3974|1624.7|336.5|1581.5|287.5|1581|1581.8|1053|1265.5|1265.9|1160.1|759.6|1160.2|1160.1|1632.6|2974.1|4081.5|1759.7|3974.1|3974.1|3831.9|
#> 100                                                                                                                                      1009|2378|
#>                                                                                         WT_GLIR
#> 2   0.5|0.6|0.1|0.1|0.25|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.265|
#> 100                                                                                    0.2|0.2|
#>                                                                                                                                                       WT_DEPTH
#> 2   1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|
#> 100                                                                                                                                                 1404|1404|
#>                                        WT_Enable
#> 2   1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 100                                         0|1|
#>                                        WT_GDEPTH
#> 2   0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 100                                         0|0|
#>                                                                                                                      WT_GPRES
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 100                                                                                                                  290|522|
#>                                                                                                         WT_RESPRES
#> 2   1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|
#> 100                                                                                                     1600|1600|
#>                                           ProsperFilename
#> 2      \\\\network\\piscis\\well_models\\PISC-M007-TS.Out
#> 100 \\\\network\\piscis\\well_models\\PISC-M026S01-TS.Out
```

``` r
library(stringr)
x <- myXl$Wellname

allIndices <- 1:length(x)
incorrectIndices <- grep("[0-9]{4}-", x, perl=TRUE)
incorrectIndices
#> [1]   2 100

xt <- strsplit(x[incorrectIndices], "-")
fn <- unlist(lapply(xt, "[", 1))
xl <- unlist(lapply(xt, "[", 2))
ct <- unlist(lapply(xt, "[", 3))


first <- str_sub(xl, 1, 1)                 # extract the 1st character
xu <- unlist(str_extract_all(xl, "\\d+"))  # extract the numeric part only
xn <- as.numeric(xu) / 1000 * 1000
xp <- str_pad(xn, pad = "0", width = 3)
wn <- paste0(first, xp)
corrected <- paste(fn, wn, ct, sep = "-")

myXl$Wellname[incorrectIndices] <- corrected

  # show the wells with issues
  myXl[!grepl("PSCO-[M,O,P,,Q,R,S][0-9][0-9][0-9]-[T,L,S]S", myXl$Wellname),]
#>       Wellname       Company Analyst Field Location Platform Fluid
#> 75 PSCO-027-TS Oil Gains Co.  Andrew PISCO  S027-TS        S     0
#>    WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 75        0         1          1           3        7 455.183    36.1
#>    PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 75        1.3             10000       0      74           3             1
#>    PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 75        208   1850.696       10        1      1695.7     217.999
#>    IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES IPR_PI   GEO_THMD
#> 75        700      2        1075       736.188   1.55 0|5141.08|
#>    GEO_THTEMP GL_method                                  GL_ArrayMandrels
#> 75   104|218|         2 1532.15|2408.14|3133.2|3697.51|4501.31|0|0|0|0|0|
#>    GL_Vdepth GL_GSG GL_CO2
#> 75   4501.31    1.2     65
#>                                                                          WT_DATE
#> 75 21/11/2013|15/04/2014|04/05/2014|12/06/2014|15/04/2014|15/01/2015|15/01/2015|
#>                              WT_THT                             WT_LIQRT
#> 75 114.8|149|149|141|110|154.4|140| 339|1261|687|1075|212|1159.1|1159.1|
#>                    WT_WC
#> 75 2|0.9|14|0|2|4.9|4.9|
#>                                                      WT_THP
#> 75 173.696|214.696|188.696|246.696|269.696|217.696|217.696|
#>                           WT_GOR                            WT_GLIR
#> 75 2626|586|950|700|500|660|500| 0.04|0.6|0.56|0.75|0.06|0.48|0.35|
#>                                                    WT_DEPTH      WT_Enable
#> 75 4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|4501.31| 1|1|1|1|1|1|0|
#>                           WT_GDEPTH
#> 75 0|0|0|5141.08|5141.08|0|5141.08|
#>                                                    WT_GPRES
#> 75 173.696|214.696|188.696|736.188|738.696|217.696|584.258|
#>                                           WT_RESPRES
#> 75 1714.7|1698.7|1695.7|1695.7|1695.7|1695.7|1695.7|
#>                                    ProsperFilename
#> 75 \\\\network\\piscis\\well_models\\PISC-S027.Out
```

### correct the platform in the well name

``` r
x <- myXl$Wellname
# pick up the well index
incorrectIndices <- !grepl("PSCO-[M,O,P,,Q,R,S][0-9][0-9][0-9]-[T,L,S]S", x)
# incorrectIndices

xt <- strsplit(x[incorrectIndices], "-")

fn <- unlist(lapply(xt, "[", 1))
xl <- unlist(lapply(xt, "[", 2))
ct <- unlist(lapply(xt, "[", 3))

xl 
#> [1] "027"
platform <- myXl$Platform[incorrectIndices]

wn <- paste0(platform, xl)

corrected <- paste(fn, wn, ct, sep = "-")
corrected
#> [1] "PSCO-S027-TS"

myXl$Wellname[incorrectIndices] <- corrected

myXl[!grepl("PSCO-[M,O,P,,Q,R,S][0-9][0-9][0-9]-[T,L,S]S", myXl$Wellname),]
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

# finished the corrections of the well name
```

### Company

``` r
myXl[!grepl("Oil Gains Co.", myXl$Company),]
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
# We don't get any return. All the company names are the same. Cool!
```

### Analyst

``` r
summary(myXl$Analyst)
#>    Length     Class      Mode 
#>       100 character character
unique(myXl$Analyst)
#>  [1] "Aida"     "Ibironke" "Ibironk"  "Vivek"    "Americo"  "Norman"  
#>  [7] "Rod"      "Rodrigo"  "Sam"      "Thomas"   "Tom"      "Kai"     
#> [13] "Andrew"   "Andy"     "Camden"   NA
```

``` r
operators <- c("Aida", "Americo", "Andrew", "Camden", "Ibironke", "Kai", "Norman", 
               "Rodrigo", "Sam", "Tom", "Vivek")

# incorrect assignements
tocorrectIndices <- which(!myXl$Analyst %in% operators)
myXl[tocorrectIndices, ]
#>        Wellname       Company Analyst Field Location Platform Fluid
#> 9  PSCO-M021-LS Oil Gains Co. Ibironk PISCO  M021-LS        M     0
#> 31 PSCO-Q032-SS Oil Gains Co.     Rod PISCO  Q032-SS        Q     0
#> 32 PSCO-Q028-LS Oil Gains Co.     Rod PISCO  Q028-LS        Q     0
#> 33 PSCO-Q028-SS Oil Gains Co.     Rod PISCO  Q028-SS        Q     0
#> 37 PSCO-Q018-LS Oil Gains Co.  Thomas PISCO  Q018-LS        Q     0
#> 78 PSCO-S011-SS Oil Gains Co.    Andy PISCO  S011-SS        S     0
#> 83 PSCO-S030-SS Oil Gains Co.    Andy PISCO  S030-SS        S     0
#> 98 PSCO-S012-LS Oil Gains Co.    <NA> PISCO  S012-LS        S     0
#>    WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 9         0         1          0           0        2 415.875      36
#> 31        0         1          0           0        4 416.000      36
#> 32        0         1          0           0        1 472.000      36
#> 33        0         1          0           0        1 472.000      36
#> 37        0         1          0           0        1 416.000      36
#> 78        0         1          0           0        9 455.183      36
#> 83        0         1          1           3        8 439.000      36
#> 98        0         1          0           0        2 350.000      36
#>    PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 9     1.20000             15000       0      65           3             0
#> 31    1.21562             15500       0      65           3             2
#> 32    1.20000             15000       0      69           3             2
#> 33    1.20000             15000       0      69           3             2
#> 37    1.20000             15500       0      65           3             1
#> 78    1.30000             15000       0      70           3             1
#> 83    1.30000             15000       0      74           3             2
#> 98    1.30000             20000       0      70           0             0
#>    PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 9   209.00000   1753.000       10        1    1526.000     202.000
#> 31  209.00000   1767.696       10        0    1300.000     209.000
#> 32  209.00000   1921.000       10        1    1560.710     210.000
#> 33  209.00000   1921.000       10        1    1560.710     210.000
#> 37  408.20001   1738.300       10        0    1080.000     212.000
#> 78   97.77777   1836.000       10        1    1485.000     107.578
#> 83  208.00000   1835.696       10        1    1480.750     206.000
#> 98         NA         NA       10        3    1620.696     206.000
#>    IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES   IPR_PI       GEO_THMD
#> 9     4735.00     90       440.8       873.840 0.688000 14.52|1543.02|
#> 31    6000.00     95         0.0         0.000 2.000000        0|2538|
#> 32    1597.00     79      1730.0       951.197 0.000000        0|1458|
#> 33    1839.00     79      1730.0       860.542 0.000000        0|1458|
#> 37    2467.00     82         0.0         0.000 2.160971        0|1761|
#> 78     940.00     44       362.0       668.011 0.628750     0|9186.35|
#> 83     500.00     17       396.0       715.239 0.700000     0|4757.22|
#> 98    2821.67     90         0.0         0.000 1.000000     0|4507.87|
#>          GEO_THTEMP GL_method
#> 9           80|202|         0
#> 31          60|209|         0
#> 32          80|210|         0
#> 33          80|210|         0
#> 37          80|206|         2
#> 78 26.6667|107.578|         2
#> 83         140|206|         0
#> 98          70|204|         2
#>                                            GL_ArrayMandrels GL_Vdepth
#> 9                601.02|906.02|1140.02|1318.02|0|0|0|0|0|0|  1318.020
#> 31                                     0|0|0|0|0|0|0|0|0|0|  2138.800
#> 32                                     0|0|0|0|0|0|0|0|0|0|  1108.000
#> 33                                     0|0|0|0|0|0|0|0|0|0|  1098.950
#> 37                        618|974|1263|1475|1609|0|0|0|0|0|  1609.200
#> 78             2369.75|5120.08|7206.36|8852.03|0|0|0|0|0|0|  8852.034
#> 83 1332.02|2109.58|2752.62|3316.93|3792.65|4199.48|0|0|0|0|  4199.480
#> 98             1756.23|2797.24|3649.93|4092.52|0|0|0|0|0|0|     0.000
#>    GL_GSG GL_CO2
#> 9     1.2     65
#> 31    1.2     65
#> 32    1.2     65
#> 33    1.2     65
#> 37    1.2     65
#> 78    1.2     65
#> 83    1.2     65
#> 98    1.2     65
#>                                                                                      WT_DATE
#> 9                                                                     14/08/2005|21/06/2005|
#> 31                                              09/04/2014|19/06/2014|12/09/2014|30/11/2014|
#> 32                                                                                     41799
#> 33                                                                                     41799
#> 37                                                                                     41953
#> 78 |25/09/2013|19/07/2013|15/06/2014|15/06/2014|11/07/2014|12/05/2014|24/01/2015|24/01/2015|
#> 83  08/08/2012|15/09/2012|09/10/2012|20/06/2012|30/07/2012|18/04/2014|21/05/2014|14/06/2014|
#> 98                                                                              |15/06/2013|
#>                                          WT_THT
#> 9                                      110|113|
#> 31                             200|200|100|120|
#> 32                                          152
#> 33                                          152
#> 37                                          127
#> 78        30.5556|55|49|59|44|45|40.5556|41|42|
#> 83 123.8|134.6|131|123.8|123.8|136.4|168.8|149|
#> 98                               64.9999|113.8|
#>                                      WT_LIQRT                       WT_WC
#> 9                               440.8|1722.5|                      90|95|
#> 31                          1674|746|392|904|                85|88|88|95|
#> 32                                       1730                          79
#> 33                                       1730                          79
#> 37                                        753                          80
#> 78      1142|350|263|455|455|529|369|362|362| 89|55|50|60|60|23|59|44|44|
#> 83 284.1|150.6|231.6|69.84|69.84|279|195|396|         0|0|0|0|0|19|20|17|
#> 98                                   585|553|                      90|95|
#>                                                         WT_THP
#> 9                                                 290.1|101.5|
#> 31                              261.696|203.696|275.696|130.5|
#> 32                                                         232
#> 33                                                         232
#> 37                                                          87
#> 78             159.304|261|232|174|174|208|143.67|265.2|265.2|
#> 83 174.24|156.84|159.74|174.24|174.24|213.346|171.839|246.696|
#> 98                                                144.696|449|
#>                                           WT_GOR
#> 9                                     4735|4382|
#> 31                          1251|5023|9526|6000|
#> 32                                          1597
#> 33                                          1839
#> 37                                          1139
#> 78     9001|3129|2827|2635|611|364|550|6247|940|
#> 83 2625|2958|2625|3217.56|3378.56|860|14012|500|
#> 98                                   1500|13115|
#>                                    WT_GLIR
#> 9                                0.18|0.2|
#> 31                       475|430|550|0.27|
#> 32                             0.275000006
#> 33                             0.282999992
#> 37                             0.200000003
#> 78      0.1|0.3|0.3|0|0.1|1|0.1|0.33|0.33|
#> 83 0.096|0.047|0|0.05|0.05|0.96|0.47|0.17|
#> 98                              0.1|0.118|
#>                                                                    WT_DEPTH
#> 9                                                                1318|1318|
#> 31                                             2138.8|2138.8|2138.8|2138.8|
#> 32                                                            1108.00001543
#> 33                                                           1098.950000391
#> 37                                                           1609.000058203
#> 78 4548.88|8851.71|8851.71|8851.71|5120.08|8851.71|2040.68|2040.68|2040.68|
#> 83         4199.48|4199.48|4199.48|4199.48|4199.48|4199.48|4199.48|4199.48|
#> 98                                                         3937.01|2795.28|
#>             WT_Enable                                  WT_GDEPTH
#> 9                0|1|                                       0|0|
#> 31           1|1|1|0|                                   0|0|0|0|
#> 32                  0                                          0
#> 33                  0                                          0
#> 37                  0                                          0
#> 78 1|1|1|1|1|1|1|1|0| 0|0|0|9186.35|9186.35|0|9186.35|0|9186.35|
#> 83   1|1|1|1|1|1|1|0|                           0|0|0|0|0|0|0|0|
#> 98               1|0|                                 0|4429.13|
#>                                                       WT_GPRES
#> 9                                                 290.1|101.5|
#> 31                              261.696|203.696|275.696|130.5|
#> 32                                                         232
#> 33                                                         232
#> 37                                                          87
#> 78  159.304|261|232|1009.48|1159.51|208|1226.67|265.2|668.011|
#> 83 174.24|156.84|159.74|174.24|174.24|213.696|171.696|246.696|
#> 98                                               144.696|1180|
#>                                              WT_RESPRES
#> 9                                            1526|1526|
#> 31                                 1300|1300|1300|1300|
#> 32                                         1560.7109375
#> 33                                         1560.7109375
#> 37                                                 1080
#> 78 1499.3|1485.3|1276.52|1485|1485|1485|1485|1485|1485|
#> 83    1500|1500|1500|1500|1500|1480.74|1480.74|1480.74|
#> 98                                       1214.7|1620.7|
#>                                       ProsperFilename
#> 9  \\\\network\\piscis\\well_models\\PISC-M021-LS.Out
#> 31 \\\\network\\piscis\\well_models\\PISC-Q032-SS.Out
#> 32 \\\\network\\piscis\\well_models\\PISC-Q028-LS.Out
#> 33 \\\\network\\piscis\\well_models\\PISC-Q028-SS.Out
#> 37 \\\\network\\piscis\\well_models\\PISC-Q018-LS.Out
#> 78 \\\\network\\piscis\\well_models\\PISC-S011-SS.Out
#> 83 \\\\network\\piscis\\well_models\\PISC-S030-SS.Out
#> 98 \\\\network\\piscis\\well_models\\PISC-S013-LS.Out
```

We can correct manually:

``` r
myXl$Analyst[9] <- "Ibironke"
myXl$Analyst[c(31,32,32,33)] = "Rodrigo"
myXl$Analyst[c(78,83)] = "Andrew"
myXl$Analyst[c(37)] = "Tom"

# verify if we have incorrect assignements
  tocorrectIndices <- which(!myXl$Analyst %in% operators)
  myXl[tocorrectIndices, ]
#>        Wellname       Company Analyst Field Location Platform Fluid
#> 98 PSCO-S012-LS Oil Gains Co.    <NA> PISCO  S012-LS        S     0
#>    WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 98        0         1          0           0        2     350      36
#>    PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 98        1.3             20000       0      70           0             0
#>    PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 98         NA         NA       10        3    1620.696         206
#>    IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES IPR_PI   GEO_THMD
#> 98    2821.67     90           0             0      1 0|4507.87|
#>    GEO_THTEMP GL_method                             GL_ArrayMandrels
#> 98    70|204|         2 1756.23|2797.24|3649.93|4092.52|0|0|0|0|0|0|
#>    GL_Vdepth GL_GSG GL_CO2      WT_DATE         WT_THT WT_LIQRT  WT_WC
#> 98         0    1.2     65 |15/06/2013| 64.9999|113.8| 585|553| 90|95|
#>          WT_THP      WT_GOR    WT_GLIR         WT_DEPTH WT_Enable
#> 98 144.696|449| 1500|13115| 0.1|0.118| 3937.01|2795.28|      1|0|
#>     WT_GDEPTH      WT_GPRES     WT_RESPRES
#> 98 0|4429.13| 144.696|1180| 1214.7|1620.7|
#>                                       ProsperFilename
#> 98 \\\\network\\piscis\\well_models\\PISC-S013-LS.Out
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
grep("[^PISCO]", myXl$Field)      # which means those which are not named like PISCO
#> [1] 12 27
```

``` r
# which row index has NAs in it
myXl[which(is.na(myXl$Field)), ]
#>       Wellname       Company  Analyst Field Location Platform Fluid
#> 7 PSCO-M016-LS Oil Gains Co. Ibironke  <NA>  M016-LS        M     0
#>   WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 7        0         1          0           0        3 419.775      35
#>   PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 7        1.2             15000       0      65           3             4
#>   PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 7        209       1722       10        0      1459.5         214
#>   IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES IPR_PI    GEO_THMD
#> 7       3676     90         560       981.644  1.018 14.52|1954|
#>   GEO_THTEMP GL_method                                  GL_ArrayMandrels
#> 7    92|214|         0 676.82|1099.42|1444.92|1675.82|1731.22|0|0|0|0|0|
#>   GL_Vdepth GL_GSG GL_CO2                           WT_DATE         WT_THT
#> 7   1675.82    1.2     65 05/05/2014|13/04/2014|17/12/2013| 125.6|125|125|
#>       WT_LIQRT     WT_WC       WT_THP          WT_GOR        WT_GLIR
#> 7 560|558|558| 90|90|90| 261|290|290| 1233|1472|3676| 0.28|0.1|0.33|
#>                   WT_DEPTH WT_Enable WT_GDEPTH     WT_GPRES
#> 7 1675.82|1675.82|1675.82|    1|1|0|    0|0|0| 261|290|290|
#>              WT_RESPRES                                    ProsperFilename
#> 7 1459.5|1459.5|1459.5| \\\\network\\piscis\\well_models\\PISC-M016-LS.Out
```

``` r
# make the correction
myXl$Field[c(7,12,27)] <- "PISCO"

# verify for bad names in field
  grep("[^PISCO]", myXl$Field)    # which means those which are not named like PISCO
#> integer(0)
  
# which row index has NAs in it
myXl[which(is.na(myXl$Field)), ]  
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
grep(pattern, myXl$Location, invert = TRUE)
#> [1] 19
# there is one non-compliant index 
# which matches what we see above
```

``` r
myXl$Location <- substr(myXl$Wellname[19], nchar(myXl$Wellname[19])-6, nchar(myXl$Wellname[19])-3)
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
grep("[MQRS]", myXl$Platform, invert = TRUE)
#> [1]  99 100
# only two not following
# since the well name is already corrected, let's use it
```

``` r
myXl$Platform <- substr(myXl$Wellname, nchar(myXl$Wellname)-6, nchar(myXl$Wellname)-6)

# verify which indices do not comply for platform
grep("[MQRS]", myXl$Platform, invert = TRUE)
#> integer(0)
# we are done here
```

``` r
# load the library xlsx
library(xlsx)

# read the raw data
myXl <- read.xlsx("./inst/extdata/oilfield_100w_raw_data.xlsx", 1)

# lowercase to uppercase
  myXl$Wellname <- toupper(myXl$Wellname)



# removing spaces
  myXl$Wellname <- gsub(" ", "", myXl$Wellname)

  
  

# complete the completion type
# We have three completion type: SS, LS and TS

  myXl$Wellname <- gsub("-L$", "-LS", myXl$Wellname)    # the dollar sign at the end, means that 
  myXl$Wellname <- gsub("-S$", "-SS", myXl$Wellname)    # we are checking at the end of the string
  myXl$Wellname <- gsub("-T$", "-TS", myXl$Wellname)

# show the wells with issues
  myXl[!grepl("PSCO-[M,O,P,,Q,R,S][0-9][0-9][0-9]-[T,L,S]S", myXl$Wellname),]
#>          Wellname       Company  Analyst Field Location Platform Fluid
#> 2   PSCO-M0007-TS Oil Gains Co.     Aida PISCO  M007-TS        M     0
#> 45  PISCO-R009-SS Oil Gains Co.     Aida PISCO  R009-SS        R     0
#> 66  PISCO-R027-LS Oil Gains Co.   Norman PISCO  R027-LS        R     0
#> 75    PSCO-027-TS Oil Gains Co.   Andrew PISCO  S027-TS        S     0
#> 100 PSCO-M0026-TS Oil Gains Co. Ibironke PISCO  M026-TS     <NA>     0
#>     WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 2          0         1          0           0       22 473.000    36.0
#> 45         0         1          0           0       15 420.000    36.0
#> 66         0         1          0           0        2 472.896    36.0
#> 75         0         1          1           3        7 455.183    36.1
#> 100        0         1          0           0        2 472.896    36.0
#>     PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 2          1.2             25000       0      65           3             2
#> 45         1.2             25000       0      65           3             2
#> 66         1.2             15000       0      65           3             2
#> 75         1.3             10000       0      74           3             1
#> 100        1.2             15000       0      65           3             2
#>     PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 2          209   1921.000       10        0     1300.00     209.000
#> 45         209   1722.000       10        0     1546.00     209.000
#> 66         209   1935.700       10        1     1373.09     215.770
#> 75         208   1850.696       10        1     1695.70     217.999
#> 100        209   1921.000       10        0     1600.00     210.000
#>     IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES IPR_PI     GEO_THMD
#> 2       1581.5     70       973.7       956.000  1.150      0|1744|
#> 45      1435.0     80         0.0         0.000  3.000   0|1667.08|
#> 66       762.0     60      1179.3      1031.980  4.400 0|2252|2580|
#> 75       700.0      2      1075.0       736.188  1.550   0|5141.08|
#> 100     1009.0     80       784.6      1043.270  1.471      0|1593|
#>                GEO_THTEMP GL_method
#> 2                 90|200|         0
#> 45                90|209|         0
#> 66  81.446|207.78|217.64|         2
#> 75               104|218|         2
#> 100               80|224|         0
#>                                       GL_ArrayMandrels GL_Vdepth GL_GSG
#> 2                614.3|1118|1422.5|1564.6|0|0|0|0|0|0|   1564.60    1.2
#> 45  187.513|298.948|378.287|436.992|480.974|0|0|0|0|0|   1241.10    1.2
#> 66        808.4|1423.9|1834.9|2175.7|2252.5|0|0|0|0|0|      0.00    1.2
#> 75   1532.15|2408.14|3133.2|3697.51|4501.31|0|0|0|0|0|   4501.31    1.2
#> 100                  569|865|1094|1276|1424|0|0|0|0|0|   1404.00    1.2
#>     GL_CO2
#> 2       65
#> 45      65
#> 66      65
#> 75      65
#> 100     65
#>                                                                                                                                                                                                                                                WT_DATE
#> 2   09/06/2014|21/08/2014|06/02/2012|17/03/2012|11/07/2012|10/08/2012|03/09/2012|05/10/2012|18/11/2012|22/01/2013|11/03/2013|10/04/2013|18/06/2013|04/07/2013|30/07/2013|23/09/2013|14/10/2013|10/11/2013|18/04/2014|21/07/2014|21/08/2014|06/09/2014|
#> 45                                                                               06/04/2013|18/06/2013|06/07/2013|26/08/2013|16/09/2013|08/11/2013|08/11/2013|08/11/2013|12/04/2014|18/06/2014|21/08/2014|30/08/2014|12/09/2014|22/11/2014|30/12/2014|
#> 66                                                                                                                                                                                                                              18/05/2013|23/12/2014|
#> 75                                                                                                                                                                       21/11/2013|15/04/2014|04/05/2014|12/06/2014|15/04/2014|15/01/2015|15/01/2015|
#> 100                                                                                                                                                                                                                             07/09/2014|13/07/2014|
#>                                                                                       WT_THT
#> 2   125|125|125|125|135|125|125|127|125|125|125|125|125|125|125|125|125|125|125|125|125|122|
#> 45                              120|120|120|120|120|120|120|120|120|120|120|120|120|120|153|
#> 66                                                                                  165|135|
#> 75                                                          114.8|149|149|141|110|154.4|140|
#> 100                                                                                 125|143|
#>                                                                                                                             WT_LIQRT
#> 2   560|528|711.2|790.6|973.7|732.4|402.5|747.8|793.5|958.9|1190.5|1135.3|909.1|1006.4|980|1013.9|550.6|551.7|591.3|528.3|528.3|560|
#> 45                                    1782.8|1197.9|1175.4|1586.8|1175.4|1174|1824|1805.4|133.7|772.9|1000.8|1000|1220.9|888.4|1342|
#> 66                                                                                                                    2253.2|1179.3|
#> 75                                                                                              339|1261|687|1075|212|1159.1|1159.1|
#> 100                                                                                                                      784.6|1200|
#>                                                                                                                          WT_WC
#> 2   70|68|65.94|80.83|75.97|74.75|75.96|75.97|73.09|77.8|76.95|76.94|61.26|75.97|71.09|71.09|71.11|71.1|67.31|68.5|68.5|70.01|
#> 45                                              90.45|85.89|85.64|80.83|85.64|85.69|79.99|80.83|79.94|83.34|80|80|85.01|80|80|
#> 66                                                                                                                      60|60|
#> 75                                                                                                       2|0.9|14|0|2|4.9|4.9|
#> 100                                                                                                                     80|80|
#>                                                                                                                        WT_THP
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 45                                           217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                                                                 246.6|232|
#> 75                                                                   173.696|214.696|188.696|246.696|269.696|217.696|217.696|
#> 100                                                                                                                  290|522|
#>                                                                                                                                              WT_GOR
#> 2   4160|3974|1624.7|336.5|1581.5|287.5|1581|1581.8|1053|1265.5|1265.9|1160.1|759.6|1160.2|1160.1|1632.6|2974.1|4081.5|1759.7|3974.1|3974.1|3831.9|
#> 45                                            5763.4|2132.7|1532.9|718.3|2392.9|5214.8|2466.9|1462.2|3358|5126.2|1090.9|3321.9|583.3|1254.6|1435.2|
#> 66                                                                                                                                     2368.52|762|
#> 75                                                                                                                    2626|586|950|700|500|660|500|
#> 100                                                                                                                                      1009|2378|
#>                                                                                         WT_GLIR
#> 2   0.5|0.6|0.1|0.1|0.25|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.265|
#> 45                                0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.27|
#> 66                                                                                   0.19|0.24|
#> 75                                                           0.04|0.6|0.56|0.75|0.06|0.48|0.35|
#> 100                                                                                    0.2|0.2|
#>                                                                                                                                                       WT_DEPTH
#> 2   1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|
#> 45                                                   1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|
#> 66                                                                                                                                              2252.5|2252.5|
#> 75                                                                                                    4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|
#> 100                                                                                                                                                 1404|1404|
#>                                        WT_Enable
#> 2   1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 45                1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 66                                          1|0|
#> 75                                1|1|1|1|1|1|0|
#> 100                                         0|1|
#>                                        WT_GDEPTH
#> 2   0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 45                0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 66                                2517.8|2517.9|
#> 75              0|0|0|5141.08|5141.08|0|5141.08|
#> 100                                         0|0|
#>                                                                                                                      WT_GPRES
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 45                                           217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                                                            1211.51|1047.2|
#> 75                                                                   173.696|214.696|188.696|736.188|738.696|217.696|584.258|
#> 100                                                                                                                  290|522|
#>                                                                                                         WT_RESPRES
#> 2   1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|
#> 45                                     1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|
#> 66                                                                                                   1373.09|1373|
#> 75                                                               1714.7|1698.7|1695.7|1695.7|1695.7|1695.7|1695.7|
#> 100                                                                                                     1600|1600|
#>                                           ProsperFilename
#> 2      \\\\network\\piscis\\well_models\\PISC-M007-TS.Out
#> 45     \\\\network\\piscis\\well_models\\PISC-R009-SS.Out
#> 66     \\\\network\\piscis\\well_models\\PISC-R027-LS.Out
#> 75        \\\\network\\piscis\\well_models\\PISC-S027.Out
#> 100 \\\\network\\piscis\\well_models\\PISC-M026S01-TS.Out
```

``` r
# remove non compliant field names
  # myXl$Wellname <- gsub("(^[PSCO])", "PSCO", myXl$Wellname)

# show the wells with issues
  myXl[!grepl("PSCO-[M,O,P,,Q,R,S][0-9][0-9][0-9]-[T,L,S]S", myXl$Wellname),]
#>          Wellname       Company  Analyst Field Location Platform Fluid
#> 2   PSCO-M0007-TS Oil Gains Co.     Aida PISCO  M007-TS        M     0
#> 45  PISCO-R009-SS Oil Gains Co.     Aida PISCO  R009-SS        R     0
#> 66  PISCO-R027-LS Oil Gains Co.   Norman PISCO  R027-LS        R     0
#> 75    PSCO-027-TS Oil Gains Co.   Andrew PISCO  S027-TS        S     0
#> 100 PSCO-M0026-TS Oil Gains Co. Ibironke PISCO  M026-TS     <NA>     0
#>     WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 2          0         1          0           0       22 473.000    36.0
#> 45         0         1          0           0       15 420.000    36.0
#> 66         0         1          0           0        2 472.896    36.0
#> 75         0         1          1           3        7 455.183    36.1
#> 100        0         1          0           0        2 472.896    36.0
#>     PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 2          1.2             25000       0      65           3             2
#> 45         1.2             25000       0      65           3             2
#> 66         1.2             15000       0      65           3             2
#> 75         1.3             10000       0      74           3             1
#> 100        1.2             15000       0      65           3             2
#>     PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 2          209   1921.000       10        0     1300.00     209.000
#> 45         209   1722.000       10        0     1546.00     209.000
#> 66         209   1935.700       10        1     1373.09     215.770
#> 75         208   1850.696       10        1     1695.70     217.999
#> 100        209   1921.000       10        0     1600.00     210.000
#>     IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES IPR_PI     GEO_THMD
#> 2       1581.5     70       973.7       956.000  1.150      0|1744|
#> 45      1435.0     80         0.0         0.000  3.000   0|1667.08|
#> 66       762.0     60      1179.3      1031.980  4.400 0|2252|2580|
#> 75       700.0      2      1075.0       736.188  1.550   0|5141.08|
#> 100     1009.0     80       784.6      1043.270  1.471      0|1593|
#>                GEO_THTEMP GL_method
#> 2                 90|200|         0
#> 45                90|209|         0
#> 66  81.446|207.78|217.64|         2
#> 75               104|218|         2
#> 100               80|224|         0
#>                                       GL_ArrayMandrels GL_Vdepth GL_GSG
#> 2                614.3|1118|1422.5|1564.6|0|0|0|0|0|0|   1564.60    1.2
#> 45  187.513|298.948|378.287|436.992|480.974|0|0|0|0|0|   1241.10    1.2
#> 66        808.4|1423.9|1834.9|2175.7|2252.5|0|0|0|0|0|      0.00    1.2
#> 75   1532.15|2408.14|3133.2|3697.51|4501.31|0|0|0|0|0|   4501.31    1.2
#> 100                  569|865|1094|1276|1424|0|0|0|0|0|   1404.00    1.2
#>     GL_CO2
#> 2       65
#> 45      65
#> 66      65
#> 75      65
#> 100     65
#>                                                                                                                                                                                                                                                WT_DATE
#> 2   09/06/2014|21/08/2014|06/02/2012|17/03/2012|11/07/2012|10/08/2012|03/09/2012|05/10/2012|18/11/2012|22/01/2013|11/03/2013|10/04/2013|18/06/2013|04/07/2013|30/07/2013|23/09/2013|14/10/2013|10/11/2013|18/04/2014|21/07/2014|21/08/2014|06/09/2014|
#> 45                                                                               06/04/2013|18/06/2013|06/07/2013|26/08/2013|16/09/2013|08/11/2013|08/11/2013|08/11/2013|12/04/2014|18/06/2014|21/08/2014|30/08/2014|12/09/2014|22/11/2014|30/12/2014|
#> 66                                                                                                                                                                                                                              18/05/2013|23/12/2014|
#> 75                                                                                                                                                                       21/11/2013|15/04/2014|04/05/2014|12/06/2014|15/04/2014|15/01/2015|15/01/2015|
#> 100                                                                                                                                                                                                                             07/09/2014|13/07/2014|
#>                                                                                       WT_THT
#> 2   125|125|125|125|135|125|125|127|125|125|125|125|125|125|125|125|125|125|125|125|125|122|
#> 45                              120|120|120|120|120|120|120|120|120|120|120|120|120|120|153|
#> 66                                                                                  165|135|
#> 75                                                          114.8|149|149|141|110|154.4|140|
#> 100                                                                                 125|143|
#>                                                                                                                             WT_LIQRT
#> 2   560|528|711.2|790.6|973.7|732.4|402.5|747.8|793.5|958.9|1190.5|1135.3|909.1|1006.4|980|1013.9|550.6|551.7|591.3|528.3|528.3|560|
#> 45                                    1782.8|1197.9|1175.4|1586.8|1175.4|1174|1824|1805.4|133.7|772.9|1000.8|1000|1220.9|888.4|1342|
#> 66                                                                                                                    2253.2|1179.3|
#> 75                                                                                              339|1261|687|1075|212|1159.1|1159.1|
#> 100                                                                                                                      784.6|1200|
#>                                                                                                                          WT_WC
#> 2   70|68|65.94|80.83|75.97|74.75|75.96|75.97|73.09|77.8|76.95|76.94|61.26|75.97|71.09|71.09|71.11|71.1|67.31|68.5|68.5|70.01|
#> 45                                              90.45|85.89|85.64|80.83|85.64|85.69|79.99|80.83|79.94|83.34|80|80|85.01|80|80|
#> 66                                                                                                                      60|60|
#> 75                                                                                                       2|0.9|14|0|2|4.9|4.9|
#> 100                                                                                                                     80|80|
#>                                                                                                                        WT_THP
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 45                                           217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                                                                 246.6|232|
#> 75                                                                   173.696|214.696|188.696|246.696|269.696|217.696|217.696|
#> 100                                                                                                                  290|522|
#>                                                                                                                                              WT_GOR
#> 2   4160|3974|1624.7|336.5|1581.5|287.5|1581|1581.8|1053|1265.5|1265.9|1160.1|759.6|1160.2|1160.1|1632.6|2974.1|4081.5|1759.7|3974.1|3974.1|3831.9|
#> 45                                            5763.4|2132.7|1532.9|718.3|2392.9|5214.8|2466.9|1462.2|3358|5126.2|1090.9|3321.9|583.3|1254.6|1435.2|
#> 66                                                                                                                                     2368.52|762|
#> 75                                                                                                                    2626|586|950|700|500|660|500|
#> 100                                                                                                                                      1009|2378|
#>                                                                                         WT_GLIR
#> 2   0.5|0.6|0.1|0.1|0.25|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.265|
#> 45                                0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.27|
#> 66                                                                                   0.19|0.24|
#> 75                                                           0.04|0.6|0.56|0.75|0.06|0.48|0.35|
#> 100                                                                                    0.2|0.2|
#>                                                                                                                                                       WT_DEPTH
#> 2   1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|
#> 45                                                   1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|
#> 66                                                                                                                                              2252.5|2252.5|
#> 75                                                                                                    4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|
#> 100                                                                                                                                                 1404|1404|
#>                                        WT_Enable
#> 2   1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 45                1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 66                                          1|0|
#> 75                                1|1|1|1|1|1|0|
#> 100                                         0|1|
#>                                        WT_GDEPTH
#> 2   0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 45                0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 66                                2517.8|2517.9|
#> 75              0|0|0|5141.08|5141.08|0|5141.08|
#> 100                                         0|0|
#>                                                                                                                      WT_GPRES
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 45                                           217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                                                            1211.51|1047.2|
#> 75                                                                   173.696|214.696|188.696|736.188|738.696|217.696|584.258|
#> 100                                                                                                                  290|522|
#>                                                                                                         WT_RESPRES
#> 2   1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|
#> 45                                     1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|
#> 66                                                                                                   1373.09|1373|
#> 75                                                               1714.7|1698.7|1695.7|1695.7|1695.7|1695.7|1695.7|
#> 100                                                                                                     1600|1600|
#>                                           ProsperFilename
#> 2      \\\\network\\piscis\\well_models\\PISC-M007-TS.Out
#> 45     \\\\network\\piscis\\well_models\\PISC-R009-SS.Out
#> 66     \\\\network\\piscis\\well_models\\PISC-R027-LS.Out
#> 75        \\\\network\\piscis\\well_models\\PISC-S027.Out
#> 100 \\\\network\\piscis\\well_models\\PISC-M026S01-TS.Out
```

``` r
# test
test <- c("PiSCO", "pISCO", "PSCO")

gsub("^(PSCO)", "PSCO", test)
#> [1] "PiSCO" "pISCO" "PSCO"
```

``` r
# show wells that do have incorrect field name
myXl[!grepl("^PSCO-", myXl$Wellname), ]
#>         Wellname       Company Analyst Field Location Platform Fluid
#> 45 PISCO-R009-SS Oil Gains Co.    Aida PISCO  R009-SS        R     0
#> 66 PISCO-R027-LS Oil Gains Co.  Norman PISCO  R027-LS        R     0
#>    WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 45        0         1          0           0       15 420.000      36
#> 66        0         1          0           0        2 472.896      36
#>    PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 45        1.2             25000       0      65           3             2
#> 66        1.2             15000       0      65           3             2
#>    PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 45        209     1722.0       10        0     1546.00      209.00
#> 66        209     1935.7       10        1     1373.09      215.77
#>    IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES IPR_PI     GEO_THMD
#> 45       1435     80         0.0          0.00    3.0   0|1667.08|
#> 66        762     60      1179.3       1031.98    4.4 0|2252|2580|
#>               GEO_THTEMP GL_method
#> 45               90|209|         0
#> 66 81.446|207.78|217.64|         2
#>                                      GL_ArrayMandrels GL_Vdepth GL_GSG
#> 45 187.513|298.948|378.287|436.992|480.974|0|0|0|0|0|    1241.1    1.2
#> 66       808.4|1423.9|1834.9|2175.7|2252.5|0|0|0|0|0|       0.0    1.2
#>    GL_CO2
#> 45     65
#> 66     65
#>                                                                                                                                                                  WT_DATE
#> 45 06/04/2013|18/06/2013|06/07/2013|26/08/2013|16/09/2013|08/11/2013|08/11/2013|08/11/2013|12/04/2014|18/06/2014|21/08/2014|30/08/2014|12/09/2014|22/11/2014|30/12/2014|
#> 66                                                                                                                                                18/05/2013|23/12/2014|
#>                                                          WT_THT
#> 45 120|120|120|120|120|120|120|120|120|120|120|120|120|120|153|
#> 66                                                     165|135|
#>                                                                                          WT_LIQRT
#> 45 1782.8|1197.9|1175.4|1586.8|1175.4|1174|1824|1805.4|133.7|772.9|1000.8|1000|1220.9|888.4|1342|
#> 66                                                                                 2253.2|1179.3|
#>                                                                             WT_WC
#> 45 90.45|85.89|85.64|80.83|85.64|85.69|79.99|80.83|79.94|83.34|80|80|85.01|80|80|
#> 66                                                                         60|60|
#>                                                                              WT_THP
#> 45 217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                       246.6|232|
#>                                                                                                   WT_GOR
#> 45 5763.4|2132.7|1532.9|718.3|2392.9|5214.8|2466.9|1462.2|3358|5126.2|1090.9|3321.9|583.3|1254.6|1435.2|
#> 66                                                                                          2368.52|762|
#>                                                          WT_GLIR
#> 45 0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.27|
#> 66                                                    0.19|0.24|
#>                                                                                                     WT_DEPTH
#> 45 1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|
#> 66                                                                                            2252.5|2252.5|
#>                         WT_Enable                      WT_GDEPTH
#> 45 1|1|1|1|1|1|1|1|1|1|1|1|1|1|0| 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 66                           1|0|                 2517.8|2517.9|
#>                                                                            WT_GPRES
#> 45 217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                  1211.51|1047.2|
#>                                                                     WT_RESPRES
#> 45 1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|
#> 66                                                               1373.09|1373|
#>                                       ProsperFilename
#> 45 \\\\network\\piscis\\well_models\\PISC-R009-SS.Out
#> 66 \\\\network\\piscis\\well_models\\PISC-R027-LS.Out
```

``` r
# same but saving the data frame
df <- myXl
pattern <- "^(?!PSCO)"
myXl[grepl(pattern, myXl$Wellname, perl = TRUE), ]
#>         Wellname       Company Analyst Field Location Platform Fluid
#> 45 PISCO-R009-SS Oil Gains Co.    Aida PISCO  R009-SS        R     0
#> 66 PISCO-R027-LS Oil Gains Co.  Norman PISCO  R027-LS        R     0
#>    WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 45        0         1          0           0       15 420.000      36
#> 66        0         1          0           0        2 472.896      36
#>    PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 45        1.2             25000       0      65           3             2
#> 66        1.2             15000       0      65           3             2
#>    PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 45        209     1722.0       10        0     1546.00      209.00
#> 66        209     1935.7       10        1     1373.09      215.77
#>    IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES IPR_PI     GEO_THMD
#> 45       1435     80         0.0          0.00    3.0   0|1667.08|
#> 66        762     60      1179.3       1031.98    4.4 0|2252|2580|
#>               GEO_THTEMP GL_method
#> 45               90|209|         0
#> 66 81.446|207.78|217.64|         2
#>                                      GL_ArrayMandrels GL_Vdepth GL_GSG
#> 45 187.513|298.948|378.287|436.992|480.974|0|0|0|0|0|    1241.1    1.2
#> 66       808.4|1423.9|1834.9|2175.7|2252.5|0|0|0|0|0|       0.0    1.2
#>    GL_CO2
#> 45     65
#> 66     65
#>                                                                                                                                                                  WT_DATE
#> 45 06/04/2013|18/06/2013|06/07/2013|26/08/2013|16/09/2013|08/11/2013|08/11/2013|08/11/2013|12/04/2014|18/06/2014|21/08/2014|30/08/2014|12/09/2014|22/11/2014|30/12/2014|
#> 66                                                                                                                                                18/05/2013|23/12/2014|
#>                                                          WT_THT
#> 45 120|120|120|120|120|120|120|120|120|120|120|120|120|120|153|
#> 66                                                     165|135|
#>                                                                                          WT_LIQRT
#> 45 1782.8|1197.9|1175.4|1586.8|1175.4|1174|1824|1805.4|133.7|772.9|1000.8|1000|1220.9|888.4|1342|
#> 66                                                                                 2253.2|1179.3|
#>                                                                             WT_WC
#> 45 90.45|85.89|85.64|80.83|85.64|85.69|79.99|80.83|79.94|83.34|80|80|85.01|80|80|
#> 66                                                                         60|60|
#>                                                                              WT_THP
#> 45 217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                       246.6|232|
#>                                                                                                   WT_GOR
#> 45 5763.4|2132.7|1532.9|718.3|2392.9|5214.8|2466.9|1462.2|3358|5126.2|1090.9|3321.9|583.3|1254.6|1435.2|
#> 66                                                                                          2368.52|762|
#>                                                          WT_GLIR
#> 45 0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.27|
#> 66                                                    0.19|0.24|
#>                                                                                                     WT_DEPTH
#> 45 1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|
#> 66                                                                                            2252.5|2252.5|
#>                         WT_Enable                      WT_GDEPTH
#> 45 1|1|1|1|1|1|1|1|1|1|1|1|1|1|0| 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 66                           1|0|                 2517.8|2517.9|
#>                                                                            WT_GPRES
#> 45 217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                  1211.51|1047.2|
#>                                                                     WT_RESPRES
#> 45 1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|
#> 66                                                               1373.09|1373|
#>                                       ProsperFilename
#> 45 \\\\network\\piscis\\well_models\\PISC-R009-SS.Out
#> 66 \\\\network\\piscis\\well_models\\PISC-R027-LS.Out
```

``` r
# attempt to replace PISCO. nOT WORKING
df <- myXl
pattern <- "(?!PSCO+)"
df$Wellname <- gsub(pattern, "\\1", df$Wellname, perl = TRUE)

df[!grepl("PSCO-[M,O,P,,Q,R,S][0-9][0-9][0-9]-[T,L,S]S", df$Wellname),]
#>          Wellname       Company  Analyst Field Location Platform Fluid
#> 2   PSCO-M0007-TS Oil Gains Co.     Aida PISCO  M007-TS        M     0
#> 45  PISCO-R009-SS Oil Gains Co.     Aida PISCO  R009-SS        R     0
#> 66  PISCO-R027-LS Oil Gains Co.   Norman PISCO  R027-LS        R     0
#> 75    PSCO-027-TS Oil Gains Co.   Andrew PISCO  S027-TS        S     0
#> 100 PSCO-M0026-TS Oil Gains Co. Ibironke PISCO  M026-TS     <NA>     0
#>     WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 2          0         1          0           0       22 473.000    36.0
#> 45         0         1          0           0       15 420.000    36.0
#> 66         0         1          0           0        2 472.896    36.0
#> 75         0         1          1           3        7 455.183    36.1
#> 100        0         1          0           0        2 472.896    36.0
#>     PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 2          1.2             25000       0      65           3             2
#> 45         1.2             25000       0      65           3             2
#> 66         1.2             15000       0      65           3             2
#> 75         1.3             10000       0      74           3             1
#> 100        1.2             15000       0      65           3             2
#>     PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 2          209   1921.000       10        0     1300.00     209.000
#> 45         209   1722.000       10        0     1546.00     209.000
#> 66         209   1935.700       10        1     1373.09     215.770
#> 75         208   1850.696       10        1     1695.70     217.999
#> 100        209   1921.000       10        0     1600.00     210.000
#>     IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES IPR_PI     GEO_THMD
#> 2       1581.5     70       973.7       956.000  1.150      0|1744|
#> 45      1435.0     80         0.0         0.000  3.000   0|1667.08|
#> 66       762.0     60      1179.3      1031.980  4.400 0|2252|2580|
#> 75       700.0      2      1075.0       736.188  1.550   0|5141.08|
#> 100     1009.0     80       784.6      1043.270  1.471      0|1593|
#>                GEO_THTEMP GL_method
#> 2                 90|200|         0
#> 45                90|209|         0
#> 66  81.446|207.78|217.64|         2
#> 75               104|218|         2
#> 100               80|224|         0
#>                                       GL_ArrayMandrels GL_Vdepth GL_GSG
#> 2                614.3|1118|1422.5|1564.6|0|0|0|0|0|0|   1564.60    1.2
#> 45  187.513|298.948|378.287|436.992|480.974|0|0|0|0|0|   1241.10    1.2
#> 66        808.4|1423.9|1834.9|2175.7|2252.5|0|0|0|0|0|      0.00    1.2
#> 75   1532.15|2408.14|3133.2|3697.51|4501.31|0|0|0|0|0|   4501.31    1.2
#> 100                  569|865|1094|1276|1424|0|0|0|0|0|   1404.00    1.2
#>     GL_CO2
#> 2       65
#> 45      65
#> 66      65
#> 75      65
#> 100     65
#>                                                                                                                                                                                                                                                WT_DATE
#> 2   09/06/2014|21/08/2014|06/02/2012|17/03/2012|11/07/2012|10/08/2012|03/09/2012|05/10/2012|18/11/2012|22/01/2013|11/03/2013|10/04/2013|18/06/2013|04/07/2013|30/07/2013|23/09/2013|14/10/2013|10/11/2013|18/04/2014|21/07/2014|21/08/2014|06/09/2014|
#> 45                                                                               06/04/2013|18/06/2013|06/07/2013|26/08/2013|16/09/2013|08/11/2013|08/11/2013|08/11/2013|12/04/2014|18/06/2014|21/08/2014|30/08/2014|12/09/2014|22/11/2014|30/12/2014|
#> 66                                                                                                                                                                                                                              18/05/2013|23/12/2014|
#> 75                                                                                                                                                                       21/11/2013|15/04/2014|04/05/2014|12/06/2014|15/04/2014|15/01/2015|15/01/2015|
#> 100                                                                                                                                                                                                                             07/09/2014|13/07/2014|
#>                                                                                       WT_THT
#> 2   125|125|125|125|135|125|125|127|125|125|125|125|125|125|125|125|125|125|125|125|125|122|
#> 45                              120|120|120|120|120|120|120|120|120|120|120|120|120|120|153|
#> 66                                                                                  165|135|
#> 75                                                          114.8|149|149|141|110|154.4|140|
#> 100                                                                                 125|143|
#>                                                                                                                             WT_LIQRT
#> 2   560|528|711.2|790.6|973.7|732.4|402.5|747.8|793.5|958.9|1190.5|1135.3|909.1|1006.4|980|1013.9|550.6|551.7|591.3|528.3|528.3|560|
#> 45                                    1782.8|1197.9|1175.4|1586.8|1175.4|1174|1824|1805.4|133.7|772.9|1000.8|1000|1220.9|888.4|1342|
#> 66                                                                                                                    2253.2|1179.3|
#> 75                                                                                              339|1261|687|1075|212|1159.1|1159.1|
#> 100                                                                                                                      784.6|1200|
#>                                                                                                                          WT_WC
#> 2   70|68|65.94|80.83|75.97|74.75|75.96|75.97|73.09|77.8|76.95|76.94|61.26|75.97|71.09|71.09|71.11|71.1|67.31|68.5|68.5|70.01|
#> 45                                              90.45|85.89|85.64|80.83|85.64|85.69|79.99|80.83|79.94|83.34|80|80|85.01|80|80|
#> 66                                                                                                                      60|60|
#> 75                                                                                                       2|0.9|14|0|2|4.9|4.9|
#> 100                                                                                                                     80|80|
#>                                                                                                                        WT_THP
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 45                                           217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                                                                 246.6|232|
#> 75                                                                   173.696|214.696|188.696|246.696|269.696|217.696|217.696|
#> 100                                                                                                                  290|522|
#>                                                                                                                                              WT_GOR
#> 2   4160|3974|1624.7|336.5|1581.5|287.5|1581|1581.8|1053|1265.5|1265.9|1160.1|759.6|1160.2|1160.1|1632.6|2974.1|4081.5|1759.7|3974.1|3974.1|3831.9|
#> 45                                            5763.4|2132.7|1532.9|718.3|2392.9|5214.8|2466.9|1462.2|3358|5126.2|1090.9|3321.9|583.3|1254.6|1435.2|
#> 66                                                                                                                                     2368.52|762|
#> 75                                                                                                                    2626|586|950|700|500|660|500|
#> 100                                                                                                                                      1009|2378|
#>                                                                                         WT_GLIR
#> 2   0.5|0.6|0.1|0.1|0.25|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.265|
#> 45                                0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.27|
#> 66                                                                                   0.19|0.24|
#> 75                                                           0.04|0.6|0.56|0.75|0.06|0.48|0.35|
#> 100                                                                                    0.2|0.2|
#>                                                                                                                                                       WT_DEPTH
#> 2   1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|
#> 45                                                   1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|
#> 66                                                                                                                                              2252.5|2252.5|
#> 75                                                                                                    4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|
#> 100                                                                                                                                                 1404|1404|
#>                                        WT_Enable
#> 2   1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 45                1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 66                                          1|0|
#> 75                                1|1|1|1|1|1|0|
#> 100                                         0|1|
#>                                        WT_GDEPTH
#> 2   0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 45                0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 66                                2517.8|2517.9|
#> 75              0|0|0|5141.08|5141.08|0|5141.08|
#> 100                                         0|0|
#>                                                                                                                      WT_GPRES
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 45                                           217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                                                            1211.51|1047.2|
#> 75                                                                   173.696|214.696|188.696|736.188|738.696|217.696|584.258|
#> 100                                                                                                                  290|522|
#>                                                                                                         WT_RESPRES
#> 2   1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|
#> 45                                     1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|
#> 66                                                                                                   1373.09|1373|
#> 75                                                               1714.7|1698.7|1695.7|1695.7|1695.7|1695.7|1695.7|
#> 100                                                                                                     1600|1600|
#>                                           ProsperFilename
#> 2      \\\\network\\piscis\\well_models\\PISC-M007-TS.Out
#> 45     \\\\network\\piscis\\well_models\\PISC-R009-SS.Out
#> 66     \\\\network\\piscis\\well_models\\PISC-R027-LS.Out
#> 75        \\\\network\\piscis\\well_models\\PISC-S027.Out
#> 100 \\\\network\\piscis\\well_models\\PISC-M026S01-TS.Out
```

``` r
# show wellls that do not comply with well naming pattern
df[!grepl("PSCO-[M,O,P,Q,R,S][0-9][0-9][0-9]-[T,L,S]S", df$Wellname),]
#>          Wellname       Company  Analyst Field Location Platform Fluid
#> 2   PSCO-M0007-TS Oil Gains Co.     Aida PISCO  M007-TS        M     0
#> 45  PISCO-R009-SS Oil Gains Co.     Aida PISCO  R009-SS        R     0
#> 66  PISCO-R027-LS Oil Gains Co.   Norman PISCO  R027-LS        R     0
#> 75    PSCO-027-TS Oil Gains Co.   Andrew PISCO  S027-TS        S     0
#> 100 PSCO-M0026-TS Oil Gains Co. Ibironke PISCO  M026-TS     <NA>     0
#>     WellType AL_Method Completion SandControl WT_COUNT PVT_GOR PVT_API
#> 2          0         1          0           0       22 473.000    36.0
#> 45         0         1          0           0       15 420.000    36.0
#> 66         0         1          0           0        2 472.896    36.0
#> 75         0         1          1           3        7 455.183    36.1
#> 100        0         1          0           0        2 472.896    36.0
#>     PVT_SG_gas PVT_WaterSalinity PVT_H2S PVT_CO2 PVT_PB_CORR PVT_VISC_CORR
#> 2          1.2             25000       0      65           3             2
#> 45         1.2             25000       0      65           3             2
#> 66         1.2             15000       0      65           3             2
#> 75         1.3             10000       0      74           3             1
#> 100        1.2             15000       0      65           3             2
#>     PVT_BPTEMP PVT_BPPRES VLP_CORR IPR_CORR IPR_RESPRES IPR_RESTEMP
#> 2          209   1921.000       10        0     1300.00     209.000
#> 45         209   1722.000       10        0     1546.00     209.000
#> 66         209   1935.700       10        1     1373.09     215.770
#> 75         208   1850.696       10        1     1695.70     217.999
#> 100        209   1921.000       10        0     1600.00     210.000
#>     IPR_TOTGOR IPR_WC IPR_VOGELRT IPR_VOGELPRES IPR_PI     GEO_THMD
#> 2       1581.5     70       973.7       956.000  1.150      0|1744|
#> 45      1435.0     80         0.0         0.000  3.000   0|1667.08|
#> 66       762.0     60      1179.3      1031.980  4.400 0|2252|2580|
#> 75       700.0      2      1075.0       736.188  1.550   0|5141.08|
#> 100     1009.0     80       784.6      1043.270  1.471      0|1593|
#>                GEO_THTEMP GL_method
#> 2                 90|200|         0
#> 45                90|209|         0
#> 66  81.446|207.78|217.64|         2
#> 75               104|218|         2
#> 100               80|224|         0
#>                                       GL_ArrayMandrels GL_Vdepth GL_GSG
#> 2                614.3|1118|1422.5|1564.6|0|0|0|0|0|0|   1564.60    1.2
#> 45  187.513|298.948|378.287|436.992|480.974|0|0|0|0|0|   1241.10    1.2
#> 66        808.4|1423.9|1834.9|2175.7|2252.5|0|0|0|0|0|      0.00    1.2
#> 75   1532.15|2408.14|3133.2|3697.51|4501.31|0|0|0|0|0|   4501.31    1.2
#> 100                  569|865|1094|1276|1424|0|0|0|0|0|   1404.00    1.2
#>     GL_CO2
#> 2       65
#> 45      65
#> 66      65
#> 75      65
#> 100     65
#>                                                                                                                                                                                                                                                WT_DATE
#> 2   09/06/2014|21/08/2014|06/02/2012|17/03/2012|11/07/2012|10/08/2012|03/09/2012|05/10/2012|18/11/2012|22/01/2013|11/03/2013|10/04/2013|18/06/2013|04/07/2013|30/07/2013|23/09/2013|14/10/2013|10/11/2013|18/04/2014|21/07/2014|21/08/2014|06/09/2014|
#> 45                                                                               06/04/2013|18/06/2013|06/07/2013|26/08/2013|16/09/2013|08/11/2013|08/11/2013|08/11/2013|12/04/2014|18/06/2014|21/08/2014|30/08/2014|12/09/2014|22/11/2014|30/12/2014|
#> 66                                                                                                                                                                                                                              18/05/2013|23/12/2014|
#> 75                                                                                                                                                                       21/11/2013|15/04/2014|04/05/2014|12/06/2014|15/04/2014|15/01/2015|15/01/2015|
#> 100                                                                                                                                                                                                                             07/09/2014|13/07/2014|
#>                                                                                       WT_THT
#> 2   125|125|125|125|135|125|125|127|125|125|125|125|125|125|125|125|125|125|125|125|125|122|
#> 45                              120|120|120|120|120|120|120|120|120|120|120|120|120|120|153|
#> 66                                                                                  165|135|
#> 75                                                          114.8|149|149|141|110|154.4|140|
#> 100                                                                                 125|143|
#>                                                                                                                             WT_LIQRT
#> 2   560|528|711.2|790.6|973.7|732.4|402.5|747.8|793.5|958.9|1190.5|1135.3|909.1|1006.4|980|1013.9|550.6|551.7|591.3|528.3|528.3|560|
#> 45                                    1782.8|1197.9|1175.4|1586.8|1175.4|1174|1824|1805.4|133.7|772.9|1000.8|1000|1220.9|888.4|1342|
#> 66                                                                                                                    2253.2|1179.3|
#> 75                                                                                              339|1261|687|1075|212|1159.1|1159.1|
#> 100                                                                                                                      784.6|1200|
#>                                                                                                                          WT_WC
#> 2   70|68|65.94|80.83|75.97|74.75|75.96|75.97|73.09|77.8|76.95|76.94|61.26|75.97|71.09|71.09|71.11|71.1|67.31|68.5|68.5|70.01|
#> 45                                              90.45|85.89|85.64|80.83|85.64|85.69|79.99|80.83|79.94|83.34|80|80|85.01|80|80|
#> 66                                                                                                                      60|60|
#> 75                                                                                                       2|0.9|14|0|2|4.9|4.9|
#> 100                                                                                                                     80|80|
#>                                                                                                                        WT_THP
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 45                                           217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                                                                 246.6|232|
#> 75                                                                   173.696|214.696|188.696|246.696|269.696|217.696|217.696|
#> 100                                                                                                                  290|522|
#>                                                                                                                                              WT_GOR
#> 2   4160|3974|1624.7|336.5|1581.5|287.5|1581|1581.8|1053|1265.5|1265.9|1160.1|759.6|1160.2|1160.1|1632.6|2974.1|4081.5|1759.7|3974.1|3974.1|3831.9|
#> 45                                            5763.4|2132.7|1532.9|718.3|2392.9|5214.8|2466.9|1462.2|3358|5126.2|1090.9|3321.9|583.3|1254.6|1435.2|
#> 66                                                                                                                                     2368.52|762|
#> 75                                                                                                                    2626|586|950|700|500|660|500|
#> 100                                                                                                                                      1009|2378|
#>                                                                                         WT_GLIR
#> 2   0.5|0.6|0.1|0.1|0.25|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.1|0.265|
#> 45                                0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.2|0.27|
#> 66                                                                                   0.19|0.24|
#> 75                                                           0.04|0.6|0.56|0.75|0.06|0.48|0.35|
#> 100                                                                                    0.2|0.2|
#>                                                                                                                                                       WT_DEPTH
#> 2   1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|1564.6|
#> 45                                                   1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|1241.1|
#> 66                                                                                                                                              2252.5|2252.5|
#> 75                                                                                                    4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|4501.31|
#> 100                                                                                                                                                 1404|1404|
#>                                        WT_Enable
#> 2   1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 45                1|1|1|1|1|1|1|1|1|1|1|1|1|1|0|
#> 66                                          1|0|
#> 75                                1|1|1|1|1|1|0|
#> 100                                         0|1|
#>                                        WT_GDEPTH
#> 2   0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 45                0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|
#> 66                                2517.8|2517.9|
#> 75              0|0|0|5141.08|5141.08|0|5141.08|
#> 100                                         0|0|
#>                                                                                                                      WT_GPRES
#> 2   246.5|1189|246.6|203|232.1|232.1|246.6|246.6|203|290.1|290.1|261.1|246.6|232.1|232.1|203|217.6|246.6|217.5|203|203|246.5|
#> 45                                           217.6|275.6|290.1|290.1|261.1|319|319|319.1|145|203|217.5|217.5|261.1|261.1|261|
#> 66                                                                                                            1211.51|1047.2|
#> 75                                                                   173.696|214.696|188.696|736.188|738.696|217.696|584.258|
#> 100                                                                                                                  290|522|
#>                                                                                                         WT_RESPRES
#> 2   1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|1300|
#> 45                                     1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|1546|
#> 66                                                                                                   1373.09|1373|
#> 75                                                               1714.7|1698.7|1695.7|1695.7|1695.7|1695.7|1695.7|
#> 100                                                                                                     1600|1600|
#>                                           ProsperFilename
#> 2      \\\\network\\piscis\\well_models\\PISC-M007-TS.Out
#> 45     \\\\network\\piscis\\well_models\\PISC-R009-SS.Out
#> 66     \\\\network\\piscis\\well_models\\PISC-R027-LS.Out
#> 75        \\\\network\\piscis\\well_models\\PISC-S027.Out
#> 100 \\\\network\\piscis\\well_models\\PISC-M026S01-TS.Out
```
