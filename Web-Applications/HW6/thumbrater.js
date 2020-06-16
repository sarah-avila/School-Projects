(function(){
    
    var thumbrater = {
        props: ['url', 'callback_url'],
        data: null,
        methods: {}
    };
    
    thumbrater.data = function() {
        var data = {
            rating: 0,
            post_indices: [0, 1, 2, 3],
            get_url: this.url,
            set_url: this.callback_url,
        };
        thumbrater.methods.load.call(data);
        return data;
    };
    
    thumbrater.methods.load = function() {
        // In use, self will correspond to the data of the table,
        // as this is called via grid.methods.load
        let self = this;
        axios.get(self.get_url)
            .then(function(res) {
                self.rating = res.data.rating;
            })
    };
    
    thumbrater.methods.compare = function (rating, second, operator) {
        let self = this;
        let first = rating;
        
        switch (operator) {
            case 'greater':
                return first > second;
            case 'greater or equal':
                return first >= second;
            case 'less':
                return first < second;
            case 'less or equal':
                return first <= second;
            default:
                alert("ERROR");
                break;
        }
    };
    
    thumbrater.methods.rate = function(rate) {
        let self = this;
        self.rating = rate;
        // send to server
        axios.get(self.set_url, {params: {rating: self.rating}});
    };
        
    utils.register_vue_component('thumbrater', 'components/thumbrater/thumbrater.html',
        function(template) {
            thumbrater.template = template.data;
            return thumbrater;
        });
})();
