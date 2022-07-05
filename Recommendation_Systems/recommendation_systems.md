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
