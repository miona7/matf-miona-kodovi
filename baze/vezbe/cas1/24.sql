select OZNAKA, NAZIV, OBIMESPB / 60 godine
from DA.STUDIJSKIPROGRAM
where OBIMESPB >= 3 * 60
order by godine, NAZIV