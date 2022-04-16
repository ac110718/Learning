import {promises as fs} from 'fs'
import { Corpus } from "tiny-tfidf";


const raw_data = await fs.readFile('iltb_all_articles.txt', 'utf8')
let archive_data = JSON.parse(raw_data)
archive_data = archive_data.sort((a, b) => {
    if (!(a.releaseTimestamp && b.releaseTimestamp)) return 1
    return a.releaseTimestamp.substring(0,10) < b.releaseTimestamp.substring(0,10) ? 1 : -1
})
const doc_names = archive_data.map(item => item.slugNumber)
const doc_text = archive_data.map(item => item.transcript ? item.transcript.toString() : "blank")
const corpus = new Corpus(doc_names, doc_text)
archive_data.forEach(item => {
    let names = item.episodeSpeakerGuestNameList.join(", ").split(/[, ]+/).map(name => name.toLowerCase())
    item.topTerms = corpus.getTopTermsForDocument(item.slugNumber).filter(word => !names.includes(word[0]))
})

async function generateHTML() {
    let outputString = `<html><head><title>Invest Like The Best Summary</title><link rel="stylesheet" href="iltb_style.css"></head><body>`
    let index_builder = `<h1><a target="_blank" href="https://www.joincolossus.com/"> All Episodes </a> </h1> <span class="index">`
    let output_builder = ``
    for (let i = 0; i < archive_data.length ; i++) {
        let item = archive_data[i]
        let title = item.title
        let speakers = item.episodeSpeakerGuestNameList.join(", ")
        let release_date = item.releaseTimestamp ? item.releaseTimestamp.substring(0,10) : "Not released"
        let ep_number = item.episodeNumber
        let tags = item.episodeCategoryNameList ? item.episodeCategoryNameList.join(", ") : ""
        let slugNumber = item.slugNumber
        let slugName = item.slugName
        let topTerms = item.topTerms.map(item=>item[0])
        let transcript = item.transcript ? item.transcript.replace(/font-family: Roboto/g,'') : ""
        
        index_builder += `
            <strong><a href="#${slugNumber}">${title}</a></strong> | ${speakers} | ${release_date} | ${ep_number} | ${tags}<br>
            <span class="keywords">[ ${topTerms.join(", ")} ]</span><br><br>`
        output_builder += `
            <h1><a name="${slugNumber}" target="_blank" href="https://www.joincolossus.com/episodes/${slugNumber}/${slugName}">${title}</a></h1>
            <h2> ${speakers} | ${release_date} | Episode: ${ep_number} | Tags: ${tags} </h2>
            ${transcript}`
    }
    index_builder += "</span>"
    outputString += index_builder
    outputString += output_builder
    await fs.writeFile('iltb_summary.html', outputString)
    console.log("Finished generating html")
}
await generateHTML()