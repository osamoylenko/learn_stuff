const axios = require('axios');

const restURL = 'WEBHOOK_URL';


(async function () {
  let lastId = 0;
  let cnt = 0;
  while (true) {
    try {

    await new Promise(resolve => setTimeout(resolve, 1000));

    const response = (await axios.post(restURL + 'crm.deal.list', {
      order: { 'ID': 'ASC' },
      filter: { '>ID': lastId, '=CONTACT_ID': '', '<=DATE_CREATE': '12.03.2024 23:59:59', '<=DATE_MODIFY': '31.03.2024 23:59:59' },
      select: ['ID', 'DATE_MODIFY'],
      start: -1
    })).data;

    const batch = {};
    response.result.forEach(element => {
      batch['command' + element['ID']] = 'crm.deal.delete?id=' + element['ID'];
      lastId = element['ID'];
      cnt++;
    });

    console.log(batch);

    if (response.result.length == 0) {
      console.log(response);
      console.log('empty!'); // иногда просто возвращается пустой список, хотя объекты, подходящие под фильтр, ещё есть
      lastId = 0;
      continue;
    }

    await axios.post(restURL + 'batch', {
      'halt': 0,
      'cmd': batch
    });

    console.log(cnt);

    } catch (e) {
      console.log(e);
      continue;
    }
  }

})();
