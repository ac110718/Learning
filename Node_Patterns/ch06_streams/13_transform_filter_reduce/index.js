import { createReadStream } from 'fs'
import {createGunzip } from 'zlib'
import parse from 'csv-parse'
import { FilterByCountry } from './filter_by_country.js'
import { SumProfit } from './sum_profit.js'
import { create } from 'domain'

const csvParser = parse({ columns: true })

createReadStream('data.csv.gz')
    .pipe(createGunzip())
    .pipe(csvParser)
    .pipe(new FilterByCountry('Italy'))
    .pipe(new SumProfit())
    .pipe(process.stdout)