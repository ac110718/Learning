## Chapter 1

Big part of search is about understanding user intent

Relevance is the art of ranking content for a search based on how much that content satisfies the needs of the user and the business:
- What content are you searching across? What types of searches (shopping vs. library card catalog)? What optimization metrics (views? Money?)
- Relevance informed heavily by user metrics

Easily tricked into seeing search as a single problem. However, application has its own unique definition of relevance.. For example Google realized relevance for the web depended on trust, not just text. 

E-commerce sites control content being searched so what matters more is affordability and highly rated products. Also need to generate profit, clear expiring inventory, and meetin supplier relationships. Search becomes the e-commerce site's salesperson. The same priorities that matter to the in-store sales experience must be programmed into the e-commerce search 

For expert search, relevant means carefully linking subjects and topics between search queries and content (what are similar topics)

Users come to search engine with great deal of baggage attached (additional data, geolocation), but also bagge is implied in the promises made by the search application. Research requires precision, casual wants recommendations

Features drive decisions. Much engineering work is in feature selection. When performing classification, you identify new features of your data to make better classification decisions. These features also help search solutions make definitive decisions about data. Signals need to correspond to decision space over which search is being performed. Curation (manipulation of content) also matters a lot in surfacing the most helpful and relevant search output.

## Chapter 2

Searching a collection of documents when you query engine. Document contains a set of fields (attributes of document, and different docs can contain different fields).

Search filters are known as facets.

Analysis converts field values (usually text) into elements called tokens, which correspond to what will ultimately be considered a match, and my match *exactly*. Search aids in matching by using language specific heuristics to transform words to simpler forms (categorization). These tokens are stored into search engine data structure when indexed.

The term dictionary is a sorted list of all terms that occur in a given field across a set of ducments. and list of documents is referred to as posting for a particular term. Term dictionary and postings list are mappings. Term dictionary maps terms to ordinal numbers that uniquely identify a term (and perhaps they can map to the same number to bucket them into the same group).

Document frequency: How often a word appears across documents ("the" will have high document frequency). Carries little discriminatory value when determining the relevancy of a document for a given search.

Term frequency: Establishes a notion of how important a document is for a given term. Number of times a term occurs in a particular document.

Term position: Posiioing often gives semantic meaning, and makes it possible to find documents based on phrase matches so that a search for "dress shoes" can match exactly in sequential positioning.