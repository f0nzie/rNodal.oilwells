
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
myXl <- read.xlsx("./inst/extdata/oilfield_100w_raw_data.xlsx", 1)
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
