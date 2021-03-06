## Chapter 1
Recommendation systems must match consumption. Some things can be recommended repeatedly, like food. Others like books or music can only be recommended until purchased.
Thin line between recommendations and advertisements. Key is trust and relevancy. Advertisements are good for the publisher, recommendations are good for the consumer. Advertisements are usually claims of a good offer, can be targeted towards specific audiences, but not usually based on user behavior or with total lack of sponsorship. Recommendations are purely to drive conversion.

Recommendation is calculated based on what the active user likes, what others have liked in the past, and what's often requested by the receiver. A commercial is given for the benefit of the sender and is usually pushed on the receiver.

Recommender systems help users discover the long tail.

When trying to optimize for diversity over accuracy, you can try to separate out by category specific recommendations, and then within that set of content, set a ranking.

Recommendations could be based on specific time of day (Sunday mornings vs. evenings), or particular context (device, geo), or boost "freshness" with a time decay ranking algorithm

Collaborative filtering employs *usage* data, while content-based filtering employs content metadata and user profiles. A mix of these two is called hybrid recommenders.

Collaborative filtering needs much feedback from users to work properly while content-based filtering needs good descriptions of the items.

## Chapter 2

Events and behaviors need to be collected to provide an indication of users tastes. Mouseovers and detail views are strong indications of interest.

Timing is tricky. If you leave immediately and never come back, it's a strong sign of disinterest, but if you come back it's the exact opposite.

sites with high user involvement enable the site owner to collect large amounts of relevant data, whereas sites with mostly one-time visitors need to focus on relationships among the content instead.

What determines an effective recommendation system? Don't go by simplistic metrics like "engagement" because user could be lost. You do NOT want slow and low conversion (wandering around lots of pages), you want fast and HIGH conversion (on target immediately). 

Allowing users to have a small sense of control or contribution towards progress can go a long way (allow subselection of recommendations, etc). Add eggs to cakebatter dramatically boosted sales from just add water.

## Chapter 4

User-item matrix stores users sentiment (rating) toward the content item. The point is to have some empty cells because your recommender system will attempt to predict what the user would put in those if they rated the corresponding items.

Sparsity problem: most users only buy one or a few items, so most of the cells are blank. The challenge is: how do you interpolate based on the data?

Algorithms that favor new items use time-decay algorithms (that have the time in the denominator to calculate a score), along with a "gravity" exponent to weight the penalty for old content.. and normal score features in the numerator.

Timing / frequency / spread of events can have significant semantic meaning. Ex: if clicks are done within a short period of time, they might not mean as much as if clicks are registered over several days.

Score is determined by weighting X # event(n) added together. Some weights can potentially be negative. Organize the data in rows so that it can be multiplied by a weight to calculate the score (via the dot product)

Inverse frequency factors into equation because interactions with less popular items provide more information about the user than interactions with popular items. (term-frequency, or user specific frequency / document-frequency, or collection frequency).

## Chapter 5

The goal of most recommender algorithms is to precalculate as much as possible to make real-time performance as fast as possible.

Memory-based means that the recommender accesses the log data in real time, while the model based signifies that the algorithm aggregates the data beforehand to make it more responsive.

Calculate recommendations based on actegories or abstractions. Remember that the abstractino or classification can't be too general because the association between categories loses its value. 

## Chapter 7

Similarity between two items is 1 if same, and 0 if nothing in common. Relationship between similarity and distance: When distance gets larger, the similarity goes toward zero. When distance goes toward zero, the similarity goes toward one.

Jaccard distance: How close are two sets to each other. Define two movies by looking at the two sets of users. Can look at # users that bought both items / # users who bought either i or j.

Measures of similarity
- L1 norm: Manhattan distance. How far apart are you on ratings on multidimensions
- L2 norm: Euclidean distance
- Cosine similarity: Dot product, divided by scaling of each factor squared. How far apart is angle X magnitude.

Use k-means clustering to segment users into different profiles. Within these subgroups you can look up the cluster, and then calculate similarities between those users as part of a smaller group. There's some risk the most similar users aren't in this group, but it's a very fast and usually accurate way to narrow down the SEARCH SPACE in calculating recommendations.

## Chapter 8

Collaborative filtering recommends a list of items for you. The list is created based on people who like the same things as you, but who also like soemthing that you haven't yet consumed. Together, we'll better understand each other.

What you want to calculate are predictions for each of the empty cells in this matrix - numbers that correspond to a particular user's predicted future sentiment toward specific content - using the data already present in the matrix.

Item similarity tends to be much more stable than user similarity, and can be pre-calculated. Try to calculate similarities for things that you have "less" of (usually items, rather than number of users). 

Data needs to be "well connected" - if there's minimal overlap, recommendations will not be good.