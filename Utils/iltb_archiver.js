import superagent from 'superagent'
import { promises as fs } from 'fs'

const api_url = 'API_URL_HERE'
let saved_data = []

async function initialize_download() {
    let first_page = await download(api_url+'0')
    let total_episodes = first_page.total
    let episodes_per_page = first_page.size
    let num_requests = Math.ceil(total_episodes/episodes_per_page)
    console.log(`page 0 downloaded..`)
    Array.from(first_page.content).forEach(episode => saved_data.push(episode))
    for (let i = 1; i <= num_requests; i++) {
        let next_page = await download(api_url+i.toString())
        console.log(`page ${i} downloaded..`)
        Array.from(next_page.content).forEach(episode => saved_data.push(episode))
    }
    await fs.writeFile('iltb_all_articles.txt', JSON.stringify(saved_data))
    let raw_data = await fs.readFile('iltb_all_articles.txt', 'utf8')
    let archive_data = JSON.parse(raw_data)
    console.log(`Saved articles: ${archive_data.length}`)
}

async function download(url) {
    const {body: contentObject} = await superagent.get(url)
    return contentObject
}

async function generateHTML() {
    let raw_data = await fs.readFile('iltb_all_articles.txt', 'utf8')
    let archive_data = JSON.parse(raw_data)
    let outputString = `<html><head><title>Invest Like The Best Archive</title><link rel="stylesheet" href="iltb_style.css"></head><body>`
    let index_builder = `<h1><a target="_blank" href="https://www.joincolossus.com/"> All Episodes </a> </h1> <span class="index">`
    let output_builder = ""
    for (let i = 0; i < archive_data.length ; i++) {
        let item = archive_data[i]
        let title = item.title
        let speakers = item.episodeSpeakerGuestNameList.join(", ")
        let release_date = item.releaseTimestamp ? item.releaseTimestamp.substring(0,10) : "Not released"
        let ep_number = item.episodeNumber
        let tags = item.episodeCategoryNameList ? item.episodeCategoryNameList.join(", ") : ""
        let slugNumber = item.slugNumber
        let slugName = item.slugName
        let transcript = item.transcript ? item.transcript.replace(/font-family: Roboto/g,'') : ""
        index_builder += `
            <strong><a href="#${slugNumber}">${title}</a></strong> | ${speakers} | ${release_date} | ${ep_number} | ${tags}<br>`
        output_builder += `
            <h1><a name="${slugNumber}" target="_blank" href="https://www.joincolossus.com/episodes/${slugNumber}/${slugName}">${title}</a></h1>
            <h2> ${speakers} | ${release_date} | Episode: ${ep_number} | Tags: ${tags} </h2>
            ${transcript}
        `
    }
    index_builder += "</span>"
    outputString += index_builder
    outputString += output_builder
    await fs.writeFile('iltb_output.html', outputString)
    console.log("Finished generating html")
}

generateHTML()
// initialize_download()