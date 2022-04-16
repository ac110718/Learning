import { extract, setSanitizeHtmlOptions, setRequestOptions } from 'article-parser'
import { data } from './data.js'
import { promises as fs } from 'fs'
import { finished } from 'stream';

// Provides a summary version of instapaper highlights put in context of original paragraph from source article

// configure article-parser

const sanitizeHtmlOptions = {
  allowedTags: [
    'h1', 'h2', 'h3', 'h4', 'h5',
    'div', 'p', 'article', 'blockquote', 'section',
    'details', 'summary',
    'pre', 'code',
    'ul', 'ol', 'li', 'dd', 'dl',
    'table', 'th', 'tr', 'td', 'thead', 'tbody', 'tfood',
    'fieldset', 'legend',
    'figure', 'figcaption', 'source',
    'iframe',
    'progress',
    'br', 'p', 'hr',
    'label',
    'abbr',
    'svg'
  ],
  allowedAttributes: {
    abbr: ['title'],
    progress: ['value', 'max'],
    source: ['src', 'srcset', 'data-srcset', 'type', 'media', 'sizes'],
    iframe: ['src', 'frameborder', 'height', 'width', 'scrolling'],
    svg: ['width', 'height']
  },
  allowedIframeDomains: ['youtube.com', 'vimeo.com']
}

setSanitizeHtmlOptions(sanitizeHtmlOptions);

// load bookmarks

class Bookmark {
  constructor(title, url) {
    this.title = title
    this.url = url
    this.highlights = []
    this.article = null
    this.outputParagraphs = []
    this.retried = false
  }
  addHighlight(text) {
    this.highlights.push(text)
  }
  async pullArticle() {
    try {
      this.article = await extract(this.url)
      process(this.article.content, this.highlights).forEach(item => this.outputParagraphs.push(item))
    } catch (err) {
      console.error(`[${this.url}] ${err.message}`)
      if (!this.retried) bm_tasks.push(pullRequest(this))
      this.retried = true
    }
  }
}

let bookmarks = new Map()
for (let item of data) {
  let bm =  bookmarks.get(item.source) || 
            bookmarks.set(item.source, new Bookmark(item.title, item.source)).get(item.source)
  bm.addHighlight(item.highlight)
}

// execute processing and downloading in manner that allows for limited concurrency

function pullRequest(bm) {
  // return a function that takes a callback
  return async (cb) => {
    console.log(`start ${bm.url}`)
    await bm.pullArticle()
    console.log(`completed ${bm.url}`)
    await cb()
  }
}

let bm_tasks = []
bookmarks.forEach(bm => bm_tasks.push(pullRequest(bm)))
const concurrency = 15
let running = 0
let completed = 0
let index = 0

function next() {
  while (running < concurrency && index < bm_tasks.length) {
    const task = bm_tasks[index++]
    console.log(`task ${index} of ${bm_tasks.length}...`)
    task(() => {
      if (++completed == bm_tasks.length) {
        return finish()
      }
      running--
      next()
    })
    running++
  }
}

async function finish() {
  let result_text = `<html><head><title>Instapaper Highlights</title><link rel="stylesheet" href="style.css"></head><body>`
  bookmarks.forEach(bm => {
    result_text += `<a href=${bm.url} target="_blank"><h1>${bm.title}</h1></a>\n`
    if (bm.outputParagraphs.length == 0) {
      bm.outputParagraphs = bm.highlights.map(highlight => {return `<p><span style="background-color: yellow;">${highlight}</span></p>`})
    }
    bm.outputParagraphs.forEach(para => {
      result_text += para
    })
    result_text += `<br>`
  })
  result_text += `</body></html>`
  await fs.writeFile('summary.html', result_text)
  console.log("Job completed")
}

next()

// map highlights to bookmarks

function process (text, highlights) {
  const para_pattern = new RegExp(`<p>(.*?)</p>`, 'gs')
  const paragraphs = text.match(para_pattern)
  return match_array(paragraphs, highlights)
}

function match_array(paragraphs, highlights) {
  const result = []
  if (paragraphs.length < 8 && (highlights.length - paragraphs.length > 4)) {
    highlights.forEach(highlight => {
      let clean_highlight = highlight.replace("\n", " ").replace(/[)]/g, "\\)").replace(/[(]/g, "\\(").replace(/[[]/g, "\\[").replace(/[]]/g, "\\]")
      result.push(`<p><span style="background-color: yellow;">${clean_highlight}</span></p>`)
    })
    return result
  }
  for (let paragraph of paragraphs) {
    let cleaned_para = paragraph.replace("\n", " ")
    let found = false
    for (let highlight of highlights) {
      highlight = highlight.replace("\n", " ").replace(/[)]/g, "\\)").replace(/[(]/g, "\\(").replace(/[[]/g, "\\[").replace(/[]]/g, "\\]")
      let matched = cleaned_para.match(highlight)
      if (matched) {
        found = true
        cleaned_para = matched.input.replace(highlight,`<span style="background-color: yellow;">${highlight}</span>`)
      }
    }
    if (found) { result.push(cleaned_para) }
  }
  return result
}

