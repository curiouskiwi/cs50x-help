# COVID CASES DAILY REPORTING
### Video Demo:  [TODO]
### Description
Every day, the New Zealand Ministry of Health posts two Excel files to their GitHub repository.  The first one has multiple sheets, one per District Health Board, that lists the daily number of Covid-19 cases reported in that district.  Data is appended each day.
The second one details, again per District, the number of people currently hospitalised due to Covid-19.  These numbers are not released on the weekend.

This project will download from GitHub the two spreadsheet files and produce reports in Markdown format suitable for posting on Reddit.

### Implementation Details
This project uses the [OpenPyXL library](https://openpyxl.readthedocs.io/en/stable/) for processing the Excel workbooks and the [Tabulate library](https://pypi.org/project/tabulate/) to format the individual reports.

The main function handles downloading and saving the files, which can then be opened with OpenPyXL.  All the numbers are taken from the various sheets and totals, running averages, etc, are calculated.  These are stored in a couple of different lists of Dict objects, for easy printing by the Tabulate library.

The program can handle special cases, such as long weekends, lack of data, etc. that can disturb the usual publication of the data spreadsheets by the MoH.  

Included in this repo is a demo XLSX file (actually the real file from 1 Oct 2022) which is used in the pytest tests.

### Challenges
The biggest challenge was handling the actual data.  For example, in one spreadsheet, the Date column was formatted as a Date field, but in the other, it was formatted as a Text field, requiring different handling.  The names were not standardised in some cases, so that required more data cleanup.  Solving the problem of handling that in an automated fashion took a long time.

### How to Run
Be sure you are connected to the internet, then run `python project.py > FILE.md` to produce the reports and create the daily output file.  I use the current date as the filename, for example, `20221002.md`.

### Sample Report:
See the included Sample Report in the repo.
