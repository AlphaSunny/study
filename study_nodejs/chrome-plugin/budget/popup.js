$(function(){
    chrome.storage.sync.get('total', function(budget) {
        $('#totalSpent').text(budget.total);
    })
    
    chrome.storage.sync.get('limit', function(budget) {
        $('#limit').text(budget.limit);
    })

    $('#spendAmount').click(function() {
        chrome.storage.sync.get('total', function(budget) {
            var newTotal = 0;
            if(budget.total) {
                newTotal += parseInt(budget.total);
            }

            var amount = $('#amount').val();
            if(amount) {
                newTotal += parseInt(amount);
            }
            
            chrome.storage.sync.set({'total': newTotal});
            $('#totalSpent').text(newTotal);
            $('#amount').val = '';
        })
    })
})